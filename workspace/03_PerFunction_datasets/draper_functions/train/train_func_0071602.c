fdtv_dvb_init(struct dvb_frontend *fe)
{
	struct firedtv *fdtv = fe->sec_priv;
	int err;


	fdtv->isochannel = fdtv->adapter.num;

	err = cmp_establish_pp_connection(fdtv, fdtv->subunit,
					  fdtv->isochannel);
	if (err) {
		dev_err(fdtv->device,
			"could not establish point to point connection\n");
		return err;
	}

	return fdtv_start_iso(fdtv);
}
