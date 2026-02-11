atmtcp_attach(struct atm_vcc *vcc,int itf)
{
	struct atm_dev *dev;

	dev = NULL;
	if (itf != -1) dev = atm_dev_lookup(itf);
	if (dev) {
		if (dev->ops != &atmtcp_v_dev_ops) {
			atm_dev_put(dev);
			return -EMEDIUMTYPE;
		}
		if (PRIV(dev)->vcc) {
			atm_dev_put(dev);
			return -EBUSY;
		}
	}
	else {
		int error;

		error = atmtcp_create(itf,0,&dev);
		if (error) return error;
	}
	PRIV(dev)->vcc = vcc;
	vcc->dev = &atmtcp_control_dev;
	vcc_insert_socket(sk_atm(vcc));
	set_bit(ATM_VF_META,&vcc->flags);
	set_bit(ATM_VF_READY,&vcc->flags);
	vcc->dev_data = dev;
	(void) atm_init_aal5(vcc);
	vcc->stats = &atmtcp_control_dev.stats.aal5;
	return dev->number;
}
