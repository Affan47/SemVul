eni_open(struct atm_vcc *vcc)
{
	struct eni_vcc *eni_vcc;
	int error;
	short vpi = vcc->vpi;
	int vci = vcc->vci;

	DPRINTK(">eni_open\n");
	EVENT("eni_open\n",0,0);
	if (!test_bit(ATM_VF_PARTIAL,&vcc->flags))
		vcc->dev_data = NULL;
	if (vci != ATM_VPI_UNSPEC && vpi != ATM_VCI_UNSPEC)
		set_bit(ATM_VF_ADDR,&vcc->flags);
	if (vcc->qos.aal != ATM_AAL0 && vcc->qos.aal != ATM_AAL5)
		return -EINVAL;
	DPRINTK(DEV_LABEL "(itf %d): open %d.%d\n",vcc->dev->number,vcc->vpi,
	    vcc->vci);
	if (!test_bit(ATM_VF_PARTIAL,&vcc->flags)) {
		eni_vcc = kmalloc(sizeof(struct eni_vcc),GFP_KERNEL);
		if (!eni_vcc) return -ENOMEM;
		vcc->dev_data = eni_vcc;
		eni_vcc->tx = NULL;
		if ((error = open_rx_first(vcc))) {
			eni_close(vcc);
			return error;
		}
		if ((error = open_tx_first(vcc))) {
			eni_close(vcc);
			return error;
		}
	}
	if (vci == ATM_VPI_UNSPEC || vpi == ATM_VCI_UNSPEC) return 0;
	if ((error = open_rx_second(vcc))) {
		eni_close(vcc);
		return error;
	}
	if ((error = open_tx_second(vcc))) {
		eni_close(vcc);
		return error;
	}
	set_bit(ATM_VF_READY,&vcc->flags);

	return 0;
}
