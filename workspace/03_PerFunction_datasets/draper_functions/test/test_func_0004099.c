hkl_geometry_factory_new(const HklGeometryConfig *config, ...)
{
	HklGeometry *geom;
	double alpha;
	va_list ap;

	geom = hkl_geometry_new();
	switch(config->type) {
		case HKL_GEOMETRY_TYPE_TWOC_VERTICAL:
			hkl_geometry_init_twoC_vertical(geom, config);
			break;
		case HKL_GEOMETRY_TYPE_EULERIAN4C_VERTICAL:
			hkl_geometry_init_eulerian4C_vertical(geom, config);
			break;
		case HKL_GEOMETRY_TYPE_KAPPA4C_VERTICAL:
			va_start(ap, config);
			alpha = va_arg(ap, double);
			va_end(ap);
			hkl_geometry_init_kappa4C_vertical(geom, config, alpha);
			break;
		case HKL_GEOMETRY_TYPE_EULERIAN6C:
			hkl_geometry_init_eulerian6C(geom, config);
			break;
		case HKL_GEOMETRY_TYPE_KAPPA6C:
			va_start(ap, config);
			alpha = va_arg(ap, double);
			va_end(ap);
			hkl_geometry_init_kappa6C(geom, config, alpha);
			break;
		case HKL_GEOMETRY_TYPE_ZAXIS:
			hkl_geometry_init_zaxis(geom, config);
			break;
	}

	return geom;
}
