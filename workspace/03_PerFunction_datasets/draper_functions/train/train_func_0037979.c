hkl_pseudo_axis_engine_mode_psi_new(char const *name,
								size_t axes_names_len,
								char const *axes_names[])
{
	HklPseudoAxisEngineModePsi *self;
	HklParameter parameters[3];
	HklFunction functions[] = {psi_func};

	if (axes_names_len != 4){
		fprintf(stderr, "This generic HklPseudoAxisEngineModePsi need exactly 4 axes");
		exit(128);
	}

	self = HKL_MALLOC(HklPseudoAxisEngineModePsi);


	hkl_parameter_init(&parameters[0],
			   "h1",
			   -1, 1, 1,
			   HKL_TRUE, HKL_FALSE,
			   NULL, NULL);


	hkl_parameter_init(&parameters[1],
			   "k1",
			   -1, 0, 1,
			   HKL_TRUE, HKL_FALSE,
			   NULL, NULL);


	hkl_parameter_init(&parameters[2],
			   "l1",
			   -1, 0, 1,
			   HKL_TRUE, HKL_FALSE,
			   NULL, NULL);


	hkl_pseudo_axis_engine_mode_init(&self->parent,
					 name,
					 hkl_pseudo_axis_engine_mode_init_psi_real,
					 hkl_pseudo_axis_engine_mode_get_psi_real,
					 hkl_pseudo_axis_engine_mode_set_real,
					 1, functions,
					 3, parameters,
					 axes_names_len, axes_names);


	return self;
}
