hkl_pseudo_axis_engine_list_factory(const HklGeometryConfig *config)
{
	HklPseudoAxisEngineList *self = NULL;

	self = hkl_pseudo_axis_engine_list_new();

	switch(config->type){
	case HKL_GEOMETRY_TYPE_TWOC_VERTICAL:
		break;
	case HKL_GEOMETRY_TYPE_EULERIAN4C_VERTICAL:
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_e4cv_hkl_new());
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_e4cv_psi_new());
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_q_new());
		break;
	case HKL_GEOMETRY_TYPE_KAPPA4C_VERTICAL:
		self->geometries->multiply = hkl_geometry_list_multiply_k4c_real;
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_k4cv_hkl_new());
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_eulerians_new());
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_k4cv_psi_new());
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_q_new());
		break;
	case HKL_GEOMETRY_TYPE_EULERIAN6C:
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_e6c_hkl_new());
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_e6c_psi_new());
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_q2_new());
		break;
	case HKL_GEOMETRY_TYPE_KAPPA6C:
		self->geometries->multiply = hkl_geometry_list_multiply_k6c_real;
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_k6c_hkl_new());
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_eulerians_new());
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_k6c_psi_new());
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_q2_new());
		break;
	case HKL_GEOMETRY_TYPE_ZAXIS:
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_zaxis_hkl_new());
		hkl_pseudo_axis_engine_list_add(self, hkl_pseudo_axis_engine_q2_new());
		break;
	}
	return self;
}
