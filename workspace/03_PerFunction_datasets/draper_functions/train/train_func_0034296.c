hash_remove_n (struct hash_subtable *st, struct hash_entry *dst_e, int32 n)
{
	int32 elemsize = st->datasize + offsetof (struct hash_entry, data[0]);
	struct hash_entry *src_e = HASH_OFFSET (dst_e, n * elemsize);
	struct hash_entry *last_e = st->last;
	int32 shift = HASH_BITS - (st->power + st->used);
	int32 index_mask = (((hash_hash_t)1) << st->power) - 1;
	int32 dst_i = (((byte *) dst_e) - ((byte *) st->entry)) / elemsize;
	int32 src_i = dst_i + n;
	hash_hash_t hash;
	int32 skip;
	int32 bytes;

	while (dst_e != src_e) {
		if (src_e <= last_e) {
			struct hash_entry *cp_e = src_e;
			int32 save_dst_i = dst_i;
			while (cp_e <= last_e && (hash = cp_e->hash) != HASH_NIL &&
			     ((hash >> shift) & index_mask) <= dst_i) {
				cp_e = HASH_OFFSET (cp_e, elemsize);
				dst_i++;
			}
			bytes = ((byte *) cp_e) - (byte *) src_e;
			memmove (dst_e, src_e, bytes);
			dst_e = HASH_OFFSET (dst_e, bytes);
			src_e = cp_e;
			src_i += dst_i - save_dst_i;
			if (src_e <= last_e && (hash = src_e->hash) != HASH_NIL) {
				skip = ((hash >> shift) & index_mask) - dst_i;
			} else {
				skip = src_i - dst_i;
			}
		} else {
			skip = src_i - dst_i;
		}
		bytes = skip * elemsize;
		memset (dst_e, HASH_NIL_MEMSET, bytes);
		dst_e = HASH_OFFSET (dst_e, bytes);
		dst_i += skip;
	}
}
