radius_paircreate(UNUSED REQUEST *request, VALUE_PAIR **vps,
			      unsigned int attribute, unsigned int vendor, int type)
{
	VALUE_PAIR *vp;

	vp = paircreate(attribute, vendor, type);
	if (!vp) {
		radlog(L_ERR, "No memory!");
		rad_assert("No memory" == NULL);
		_exit(1);
	}

	if (vps) pairadd(vps, vp);

	return vp;
}
