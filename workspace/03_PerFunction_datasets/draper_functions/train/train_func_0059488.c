efx_farch_filter_make_id(const struct efx_farch_filter_spec *spec,
			 unsigned int index)
{
	unsigned int range;

	range = efx_farch_filter_type_match_pri[spec->type];
	if (!(spec->flags & EFX_FILTER_FLAG_RX))
		range += EFX_FARCH_FILTER_MATCH_PRI_COUNT;

	return range << EFX_FARCH_FILTER_INDEX_WIDTH | index;
}
