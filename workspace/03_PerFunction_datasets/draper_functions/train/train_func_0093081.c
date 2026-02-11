skd_sg_io_put_status(struct skd_device *skdev,
				struct skd_sg_io *sksgio)
{
	struct sg_io_hdr *sgp = &sksgio->sg;
	struct skd_special_context *skspcl = sksgio->skspcl;
	int resid = 0;

	u32 nb = be32_to_cpu(skspcl->req.completion.num_returned_bytes);

	sgp->status = skspcl->req.completion.status;
	resid = sksgio->dxfer_len - nb;

	sgp->masked_status = sgp->status & STATUS_MASK;
	sgp->msg_status = 0;
	sgp->host_status = 0;
	sgp->driver_status = 0;
	sgp->resid = resid;
	if (sgp->masked_status || sgp->host_status || sgp->driver_status)
		sgp->info |= SG_INFO_CHECK;

	pr_debug("%s:%s:%d status %x masked %x resid 0x%x\n",
		 skdev->name, __func__, __LINE__,
		 sgp->status, sgp->masked_status, sgp->resid);

	if (sgp->masked_status == SAM_STAT_CHECK_CONDITION) {
		if (sgp->mx_sb_len > 0) {
			struct fit_comp_error_info *ei = &skspcl->req.err_info;
			u32 nbytes = sizeof(*ei);

			nbytes = min_t(u32, nbytes, sgp->mx_sb_len);

			sgp->sb_len_wr = nbytes;

			if (__copy_to_user(sgp->sbp, ei, nbytes)) {
				pr_debug("%s:%s:%d copy_to_user sense failed %p\n",
					 skdev->name, __func__, __LINE__,
					 sgp->sbp);
				return -EFAULT;
			}
		}
	}

	if (__copy_to_user(sksgio->argp, sgp, sizeof(sg_io_hdr_t))) {
		pr_debug("%s:%s:%d copy_to_user sg failed %p\n",
			 skdev->name, __func__, __LINE__, sksgio->argp);
		return -EFAULT;
	}

	return 0;
}
