c4iw_get_qp(struct ib_device *dev, int qpn)
{
	PDBG("%s ib_dev %p qpn 0x%x\n", __func__, dev, qpn);
	return (struct ib_qp *)get_qhp(to_c4iw_dev(dev), qpn);
}
