efx_siena_sriov_probe(struct efx_nic *efx)
{
	unsigned count;

	if (!max_vfs)
		return;

	if (efx_siena_sriov_cmd(efx, false, &efx->vi_scale, &count)) {
		netif_info(efx, probe, efx->net_dev, "no SR-IOV VFs probed\n");
		return;
	}
	if (count > 0 && count > max_vfs)
		count = max_vfs;


	efx->vf_count = count;

	efx->extra_channel_type[EFX_EXTRA_CHANNEL_IOV] = &efx_siena_sriov_channel_type;
}
