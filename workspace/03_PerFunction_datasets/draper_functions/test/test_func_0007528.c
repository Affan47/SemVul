anwcs_get_radec_bounds(const anwcs_t* wcs, int stepsize,
							double* pramin, double* pramax,
							double* pdecmin, double* pdecmax) {
	assert(wcs);
	switch (wcs->type) {
	case ANWCS_TYPE_WCSLIB:
#ifdef WCSLIB_EXISTS
		{
			anwcslib_t* anwcslib = wcs->data;
			wcslib_radec_bounds(wcs, anwcslib, stepsize, pramin, pramax, pdecmin, pdecmax);
		}
#else
		ERROR("Wcslib support was not compiled in");
#endif
		break;
	case ANWCS_TYPE_SIP:
		{
			sip_t* sip = wcs->data;
			sip_get_radec_bounds(sip, stepsize, pramin, pramax, pdecmin, pdecmax);
			break;
		}
	default:
		ERROR("Unknown anwcs type %i", wcs->type);
		break;
	}

}
