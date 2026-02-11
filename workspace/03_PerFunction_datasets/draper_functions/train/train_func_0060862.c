append_str(struct fmt_rrsig_info *info, const char *str, size_t l)
{
	if (info->buf)
	{
		memcpy(info->buf, str, l);

		info->buf += l;
	}

	info->n += l;
}
