msb_read_page(struct msb_data *msb,
	u16 pba, u8 page, struct ms_extra_data_register *extra,
					struct scatterlist *sg,  int offset)
{
	int try, error;

	if (pba == MS_BLOCK_INVALID) {
		unsigned long flags;
		struct sg_mapping_iter miter;
		size_t len = msb->page_size;

		dbg_verbose("read unmapped sector. returning 0xFF");

		local_irq_save(flags);
		sg_miter_start(&miter, sg, sg_nents(sg),
				SG_MITER_ATOMIC | SG_MITER_TO_SG);

		while (sg_miter_next(&miter) && len > 0) {

			int chunklen;

			if (offset && offset >= miter.length) {
				offset -= miter.length;
				continue;
			}

			chunklen = min(miter.length - offset, len);
			memset(miter.addr + offset, 0xFF, chunklen);
			len -= chunklen;
			offset = 0;
		}

		sg_miter_stop(&miter);
		local_irq_restore(flags);

		if (offset)
			return -EFAULT;

		if (extra)
			memset(extra, 0xFF, sizeof(*extra));
		return 0;
	}

	if (pba >= msb->block_count) {
		pr_err("BUG: attempt to read beyond the end of the card at pba %d", pba);
		return -EINVAL;
	}

	for (try = 1; try < 3; try++) {
		msb->regs.param.block_address = cpu_to_be16(pba);
		msb->regs.param.page_address = page;
		msb->regs.param.cp = MEMSTICK_CP_PAGE;

		msb->current_sg = sg;
		msb->current_sg_offset = offset;
		error = msb_run_state_machine(msb, h_msb_read_page);


		if (error == -EUCLEAN) {
			pr_notice("correctable error on pba %d, page %d",
				pba, page);
			error = 0;
		}

		if (!error && extra)
			*extra = msb->regs.extra_data;

		if (!error || msb_reset(msb, true))
			break;

	}


	if (error == -EBADMSG) {
		pr_err("uncorrectable error on read of pba %d, page %d",
			pba, page);

		if (msb->regs.extra_data.overwrite_flag &
					MEMSTICK_OVERWRITE_PGST0)
			msb_mark_page_bad(msb, pba, page);
		return -EBADMSG;
	}

	if (error)
		pr_err("read of pba %d, page %d failed with error %d",
			pba, page, error);
	return error;
}
