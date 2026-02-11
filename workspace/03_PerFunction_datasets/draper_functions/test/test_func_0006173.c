efx_wanted_parallelism(struct efx_nic *efx)
{
	cpumask_var_t thread_mask;
	unsigned int count;
	int cpu;

	if (rss_cpus) {
		count = rss_cpus;
	} else {
		if (unlikely(!zalloc_cpumask_var(&thread_mask, GFP_KERNEL))) {
			netif_warn(efx, probe, efx->net_dev,
				   "RSS disabled due to allocation failure\n");
			return 1;
		}

		count = 0;
		for_each_online_cpu(cpu) {
			if (!cpumask_test_cpu(cpu, thread_mask)) {
				++count;
				cpumask_or(thread_mask, thread_mask,
					   topology_sibling_cpumask(cpu));
			}
		}

		free_cpumask_var(thread_mask);
	}


#ifdef CONFIG_SFC_SRIOV
	if (efx->type->sriov_wanted) {
		if (efx->type->sriov_wanted(efx) && efx_vf_size(efx) > 1 &&
		    count > efx_vf_size(efx)) {
			netif_warn(efx, probe, efx->net_dev,
				   "Reducing number of RSS channels from %u to %u for "
				   "VF support. Increase vf-msix-limit to use more "
				   "channels on the PF.\n",
				   count, efx_vf_size(efx));
			count = efx_vf_size(efx);
		}
	}
#endif

	return count;
}
