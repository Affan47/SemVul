hkl_pseudo_axis_engine_select_mode(HklPseudoAxisEngine *self,
					size_t idx)
{
	if(!self || idx > HKL_LIST_LEN(self->modes))
		return;

	self->mode = self->modes[idx];
	hkl_pseudo_axis_engine_prepare_internal(self);
}
