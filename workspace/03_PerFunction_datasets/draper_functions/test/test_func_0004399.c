uv_nmi_wait(int master)
{

	this_cpu_write(uv_cpu_nmi.state, UV_NMI_STATE_IN);


	if (!master)
		return;

	do {

		if (!uv_nmi_wait_cpus(1))
			break;


		pr_alert("UV: Sending NMI IPI to %d non-responding CPUs: %*pbl\n",
			 cpumask_weight(uv_nmi_cpu_mask),
			 cpumask_pr_args(uv_nmi_cpu_mask));

		uv_nmi_nr_cpus_ping();


		if (!uv_nmi_wait_cpus(0))
			break;

		pr_alert("UV: %d CPUs not in NMI loop: %*pbl\n",
			 cpumask_weight(uv_nmi_cpu_mask),
			 cpumask_pr_args(uv_nmi_cpu_mask));
	} while (0);

	pr_alert("UV: %d of %d CPUs in NMI\n",
		atomic_read(&uv_nmi_cpus_in_nmi), num_online_cpus());
}
