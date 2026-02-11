xlog_valid_rec_header(struct xlog_rec_header *rhead)
{
	uint32_t hlen;

	if (rhead->h_magicno != cpu_to_be32(XLOG_HEADER_MAGIC_NUM))
		return 0;

	if (!rhead->h_version ||
            (be32_to_cpu(rhead->h_version) & (~XLOG_VERSION_OKBITS)))
		return 0;


	hlen = be32_to_cpu(rhead->h_len);
	if (hlen <= 0 || hlen > INT_MAX)
		return 0;

	if (rhead->h_fmt != cpu_to_be32(XLOG_FMT_LINUX_LE) &&
	    rhead->h_fmt != cpu_to_be32(XLOG_FMT_LINUX_BE) &&
	    rhead->h_fmt != cpu_to_be32(XLOG_FMT_IRIX_BE))
		return 0;

	return 1;
}
