dvb_set_sys(struct dvb_v5_fe_parms *parms,
			  fe_delivery_system_t sys)
{
	struct dtv_property dvb_prop[1];
	struct dtv_properties prop;
	int rc;

	if (sys != parms->current_sys) {

		if (dvb_fe_is_satellite(parms->current_sys) &&
		    !dvb_fe_is_satellite(sys))
			dvb_fe_sec_voltage(parms, 0, 0);


		if (parms->legacy_fe)
			return EINVAL;

		dvb_prop[0].cmd = DTV_DELIVERY_SYSTEM;
		dvb_prop[0].u.data = sys;
		prop.num = 1;
		prop.props = dvb_prop;

		if (ioctl(parms->fd, FE_SET_PROPERTY, &prop) == -1) {
			dvb_perror("Set delivery system");
			return errno;
		}
	}

	rc = dvb_add_parms_for_sys(parms->dvb_prop,
				   ARRAY_SIZE(parms->dvb_prop), sys);
	if (rc < 0)
		return EINVAL;

	parms->current_sys = sys;
	parms->n_props = rc;

	return 0;
}
