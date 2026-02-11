efx_ef10_update_stats_vf(struct efx_nic *efx, u64 *full_stats,
				       struct rtnl_link_stats64 *core_stats)
{
	if (efx_ef10_try_update_nic_stats_vf(efx))
		return 0;

	return efx_ef10_update_stats_common(efx, full_stats, core_stats);
}
