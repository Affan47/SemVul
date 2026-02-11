raid5_alloc_percpu(struct r5conf *conf)
{
	unsigned long cpu;
	int err = 0;

	conf->percpu = alloc_percpu(struct raid5_percpu);
	if (!conf->percpu)
		return -ENOMEM;

#ifdef CONFIG_HOTPLUG_CPU
	conf->cpu_notify.notifier_call = raid456_cpu_notify;
	conf->cpu_notify.priority = 0;
	err = register_cpu_notifier(&conf->cpu_notify);
	if (err)
		return err;
#endif

	get_online_cpus();
	for_each_present_cpu(cpu) {
		err = alloc_scratch_buffer(conf, per_cpu_ptr(conf->percpu, cpu));
		if (err) {
			pr_err("%s: failed memory allocation for cpu%ld\n",
			       __func__, cpu);
			break;
		}
	}
	put_online_cpus();

	if (!err) {
		conf->scribble_disks = max(conf->raid_disks,
			conf->previous_raid_disks);
		conf->scribble_sectors = max(conf->chunk_sectors,
			conf->prev_chunk_sectors);
	}
	return err;
}
