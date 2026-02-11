hkl_pseudo_axis_engine_mode_free(HklPseudoAxisEngineMode *self)
{
	HKL_LIST_FREE(self->functions);
	HKL_LIST_FREE(self->parameters);
	HKL_LIST_FREE(self->axes_names);

	if(self->geometry_init){
		hkl_geometry_free(self->geometry_init);
		self->geometry_init = NULL;
	}
	if(self->detector_init){
		hkl_detector_free(self->detector_init);
		self->detector_init = NULL;
	}
	if(self->sample_init){
		hkl_sample_free(self->sample_init);
		self->sample_init = NULL;
	}
	free(self);
}
