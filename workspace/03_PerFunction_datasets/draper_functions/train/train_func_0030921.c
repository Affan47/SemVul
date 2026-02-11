enic_dev_deinit(struct enic *enic)
{
	unsigned int i;

	for (i = 0; i < enic->rq_count; i++) {
		napi_hash_del(&enic->napi[i]);
		netif_napi_del(&enic->napi[i]);
	}
	if (vnic_dev_get_intr_mode(enic->vdev) == VNIC_DEV_INTR_MODE_MSIX)
		for (i = 0; i < enic->wq_count; i++)
			netif_napi_del(&enic->napi[enic_cq_wq(enic, i)]);

	enic_free_vnic_resources(enic);
	enic_clear_intr_mode(enic);
	enic_free_affinity_hint(enic);
}
