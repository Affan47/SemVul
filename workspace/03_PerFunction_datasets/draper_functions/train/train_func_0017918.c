verity_verify_level(struct dm_verity_io *io, sector_t block,
			       int level, bool skip_unverified)
{
	struct dm_verity *v = io->v;
	struct dm_buffer *buf;
	struct buffer_aux *aux;
	u8 *data;
	int r;
	sector_t hash_block;
	unsigned offset;

	verity_hash_at_level(v, block, level, &hash_block, &offset);

	data = dm_bufio_read(v->bufio, hash_block, &buf);
	if (IS_ERR(data))
		return PTR_ERR(data);

	aux = dm_bufio_get_aux_data(buf);

	if (!aux->hash_verified) {
		struct shash_desc *desc;
		u8 *result;

		if (skip_unverified) {
			r = 1;
			goto release_ret_r;
		}

		desc = io_hash_desc(v, io);
		desc->tfm = v->tfm;
		desc->flags = CRYPTO_TFM_REQ_MAY_SLEEP;
		r = crypto_shash_init(desc);
		if (r < 0) {
			DMERR("crypto_shash_init failed: %d", r);
			goto release_ret_r;
		}

		if (likely(v->version >= 1)) {
			r = crypto_shash_update(desc, v->salt, v->salt_size);
			if (r < 0) {
				DMERR("crypto_shash_update failed: %d", r);
				goto release_ret_r;
			}
		}

		r = crypto_shash_update(desc, data, 1 << v->hash_dev_block_bits);
		if (r < 0) {
			DMERR("crypto_shash_update failed: %d", r);
			goto release_ret_r;
		}

		if (!v->version) {
			r = crypto_shash_update(desc, v->salt, v->salt_size);
			if (r < 0) {
				DMERR("crypto_shash_update failed: %d", r);
				goto release_ret_r;
			}
		}

		result = io_real_digest(v, io);
		r = crypto_shash_final(desc, result);
		if (r < 0) {
			DMERR("crypto_shash_final failed: %d", r);
			goto release_ret_r;
		}
		if (unlikely(memcmp(result, io_want_digest(v, io), v->digest_size))) {
			if (verity_handle_err(v, DM_VERITY_BLOCK_TYPE_METADATA,
					      hash_block)) {
				r = -EIO;
				goto release_ret_r;
			}
		} else
			aux->hash_verified = 1;
	}

	data += offset;

	memcpy(io_want_digest(v, io), data, v->digest_size);

	dm_bufio_release(buf);
	return 0;

release_ret_r:
	dm_bufio_release(buf);

	return r;
}
