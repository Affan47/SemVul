sd_dif_prepare(struct scsi_cmnd *scmd)
{
	const int tuple_sz = sizeof(struct t10_pi_tuple);
	struct bio *bio;
	struct scsi_disk *sdkp;
	struct t10_pi_tuple *pi;
	u32 phys, virt;

	sdkp = scsi_disk(scmd->request->rq_disk);

	if (sdkp->protection_type == SD_DIF_TYPE3_PROTECTION)
		return;

	phys = scsi_prot_ref_tag(scmd);

	__rq_for_each_bio(bio, scmd->request) {
		struct bio_integrity_payload *bip = bio_integrity(bio);
		struct bio_vec iv;
		struct bvec_iter iter;
		unsigned int j;


		if (bip->bip_flags & BIP_MAPPED_INTEGRITY)
			break;

		virt = bip_get_seed(bip) & 0xffffffff;

		bip_for_each_vec(iv, bip, iter) {
			pi = kmap_atomic(iv.bv_page) + iv.bv_offset;

			for (j = 0; j < iv.bv_len; j += tuple_sz, pi++) {

				if (be32_to_cpu(pi->ref_tag) == virt)
					pi->ref_tag = cpu_to_be32(phys);

				virt++;
				phys++;
			}

			kunmap_atomic(pi);
		}

		bip->bip_flags |= BIP_MAPPED_INTEGRITY;
	}
}
