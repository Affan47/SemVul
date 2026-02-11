quiesce_rx(struct adapter *adap)
{
	int i;

	for (i = 0; i < SGE_QSETS; i++)
		if (adap->sge.qs[i].adap)
			napi_disable(&adap->sge.qs[i].napi);
}
