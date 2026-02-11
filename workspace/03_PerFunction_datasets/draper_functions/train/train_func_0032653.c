xgbe_dump_rx_desc(struct xgbe_prv_data *pdata, struct xgbe_ring *ring,
		       unsigned int idx)
{
	struct xgbe_ring_data *rdata;
	struct xgbe_ring_desc *rdesc;

	rdata = XGBE_GET_DESC_DATA(ring, idx);
	rdesc = rdata->rdesc;
	netdev_dbg(pdata->netdev,
		   "RX_NORMAL_DESC[%d RX BY DEVICE] = %08x:%08x:%08x:%08x\n",
		   idx, le32_to_cpu(rdesc->desc0), le32_to_cpu(rdesc->desc1),
		   le32_to_cpu(rdesc->desc2), le32_to_cpu(rdesc->desc3));
}
