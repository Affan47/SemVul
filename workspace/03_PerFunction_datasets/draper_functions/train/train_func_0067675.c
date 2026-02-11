sd_dif_complete(struct scsi_cmnd *scmd, unsigned int good_bytes)
{
	const int tuple_sz = sizeof(struct t10_pi_tuple);
	struct scsi_disk *sdkp;
	struct bio *bio;
	struct t10_pi_tuple *pi;
	unsigned int j, intervals;
	u32 phys, virt;

	sdkp = scsi_disk(scmd->request->rq_disk);

	if (sdkp->protection_type == SD_DIF_TYPE3_PROTECTION || good_bytes == 0)
		return;

	intervals = good_bytes / scsi_prot_interval(scmd);
	phys = scsi_prot_ref_tag(scmd);

	__rq_for_each_bio(bio, scmd->request) {
		struct bio_integrity_payload *bip = bio_integrity(bio);
		struct bio_vec iv;
		struct bvec_iter iter;

		virt = bip_get_seed(bip) & 0xffffffff;

		bip_for_each_vec(iv, bip, iter) {
			pi = kmap_atomic(iv.bv_page) + iv.bv_offset;

			for (j = 0; j < iv.bv_len; j += tuple_sz, pi++) {

				if (intervals == 0) {
					kunmap_atomic(pi);
					return;
				}

				if (be32_to_cpu(pi->ref_tag) == phys)
					pi->ref_tag = cpu_to_be32(virt);

				virt++;
				phys++;
				intervals--;
			}

			kunmap_atomic(pi);
		}
	}
}
