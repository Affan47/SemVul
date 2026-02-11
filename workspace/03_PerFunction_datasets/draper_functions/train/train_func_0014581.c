initialise_cpus(void)
{
	int i;

	act_cpus = 0;

	if (maxcpus > 1) {
		smp_find_cpus();

		if (num_cpus > maxcpus) {
			num_cpus = maxcpus;
		}

		for(i = 0; i < num_cpus; i++) {
			if (cpu_mask[i]) {
				act_cpus++;
			}
		}
	} else {
		act_cpus = found_cpus = num_cpus = 1;
	}


	barrier_init(act_cpus);


	for(i = 1; i < num_cpus; i++) {

	    if (cpu_mask[i]) {
	        smp_boot_ap(i);
	    }
	}

}
