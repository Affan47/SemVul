s5p_mfc_set_dec_stream_buffer_v6(struct s5p_mfc_ctx *ctx,
			int buf_addr, unsigned int start_num_byte,
			unsigned int strm_size)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	const struct s5p_mfc_regs *mfc_regs = dev->mfc_regs;
	struct s5p_mfc_buf_size *buf_size = dev->variant->buf_size;

	mfc_debug_enter();
	mfc_debug(2, "inst_no: %d, buf_addr: 0x%08x,\n"
		"buf_size: 0x%08x (%d)\n",
		ctx->inst_no, buf_addr, strm_size, strm_size);
	writel(strm_size, mfc_regs->d_stream_data_size);
	writel(buf_addr, mfc_regs->d_cpb_buffer_addr);
	writel(buf_size->cpb, mfc_regs->d_cpb_buffer_size);
	writel(start_num_byte, mfc_regs->d_cpb_buffer_offset);

	mfc_debug_leave();
	return 0;
}
