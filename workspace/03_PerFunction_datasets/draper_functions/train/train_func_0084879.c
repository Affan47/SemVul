stv0900_set_bandwidth(struct dvb_frontend *fe, u32 bandwidth)
{
	struct dvb_frontend_ops *frontend_ops = NULL;
	struct dvb_tuner_ops *tuner_ops = NULL;

	frontend_ops = &fe->ops;
	tuner_ops = &frontend_ops->tuner_ops;

	if (tuner_ops->set_bandwidth) {
		if ((tuner_ops->set_bandwidth(fe, bandwidth)) < 0)
			dprintk("%s: Invalid parameter\n", __func__);
		else
			dprintk("%s: Bandwidth=%d\n", __func__, bandwidth);

	}
}
