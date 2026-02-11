enable_rx(struct adapter *adapter)
{
	int rxq;
	struct sge *s = &adapter->sge;

	for_each_ethrxq(s, rxq)
		qenable(&s->ethrxq[rxq].rspq);
	qenable(&s->fw_evtq);


	if (adapter->flags & USING_MSI)
		t4_write_reg(adapter, T4VF_SGE_BASE_ADDR + SGE_VF_GTS,
			     CIDXINC_V(0) |
			     SEINTARM_V(s->intrq.intr_params) |
			     INGRESSQID_V(s->intrq.cntxt_id));

}
