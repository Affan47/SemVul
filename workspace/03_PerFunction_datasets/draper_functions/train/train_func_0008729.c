qlcnic_intr(int irq, void *data)
{
	struct qlcnic_host_sds_ring *sds_ring = data;
	struct qlcnic_adapter *adapter = sds_ring->adapter;

	if (qlcnic_clear_legacy_intr(adapter) == IRQ_NONE)
		return IRQ_NONE;

	napi_schedule(&sds_ring->napi);

	return IRQ_HANDLED;
}
