find_mtype(uint32_t mtype, const unsigned versions)
{
	const struct lgfs2_metadata *m = lgfs2_metadata;
	unsigned n = 0;

	do {
		if ((m[n].versions & versions) && m[n].mh_type == mtype)
			return &m[n];
		n++;
	} while (n < lgfs2_metadata_size);

	return NULL;
}
