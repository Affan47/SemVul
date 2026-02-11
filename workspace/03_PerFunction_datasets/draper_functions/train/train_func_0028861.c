sd_setup_protect_cmnd(struct scsi_cmnd *scmd,
					   unsigned int dix, unsigned int dif)
{
	struct bio *bio = scmd->request->bio;
	unsigned int prot_op = sd_prot_op(rq_data_dir(scmd->request), dix, dif);
	unsigned int protect = 0;

	if (dix) {
		if (bio_integrity_flagged(bio, BIP_IP_CHECKSUM))
			scmd->prot_flags |= SCSI_PROT_IP_CHECKSUM;

		if (bio_integrity_flagged(bio, BIP_CTRL_NOCHECK) == false)
			scmd->prot_flags |= SCSI_PROT_GUARD_CHECK;
	}

	if (dif != SD_DIF_TYPE3_PROTECTION) {
		scmd->prot_flags |= SCSI_PROT_REF_INCREMENT;

		if (bio_integrity_flagged(bio, BIP_CTRL_NOCHECK) == false)
			scmd->prot_flags |= SCSI_PROT_REF_CHECK;
	}

	if (dif) {
		scmd->prot_flags |= SCSI_PROT_TRANSFER_PI;

		if (bio_integrity_flagged(bio, BIP_DISK_NOCHECK))
			protect = 3 << 5;
		else
			protect = 1 << 5;
	}

	scsi_set_prot_op(scmd, prot_op);
	scsi_set_prot_type(scmd, dif);
	scmd->prot_flags &= sd_prot_flag_mask(prot_op);

	return protect;
}
