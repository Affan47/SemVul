cnic_cm_cleanup(struct cnic_sock *csk)
{
	if (csk->src_port) {
		struct cnic_dev *dev = csk->dev;
		struct cnic_local *cp = dev->cnic_priv;

		cnic_free_id(&cp->csk_port_tbl, be16_to_cpu(csk->src_port));
		csk->src_port = 0;
	}
}
