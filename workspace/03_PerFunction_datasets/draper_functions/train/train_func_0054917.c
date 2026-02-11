mthca_max_inline_data(struct mthca_pd *pd, int max_data_size)
{

	return pd->ibpd.uobject ? max_data_size - MTHCA_INLINE_HEADER_SIZE : 0;
}
