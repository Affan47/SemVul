hkl_pseudo_axis_engine_list_get(HklPseudoAxisEngineList *self)
{
	size_t i;
	int res = HKL_SUCCESS;

	if (!self)
		return res;

	for(i=0; i<HKL_LIST_LEN(self->engines); ++i)
		if (!hkl_pseudo_axis_engine_get(self->engines[i], NULL))
			res = HKL_FAIL;

	return res;
}
