ptc_seq_show(struct seq_file *file, void *data)
{
	struct ptc_stats *stat;
	struct bau_control *bcp;
	int cpu;

	cpu = *(loff_t *)data;
	if (!cpu) {
		seq_puts(file,
			 "# cpu bauoff sent stime self locals remotes ncpus localhub ");
		seq_puts(file, "remotehub numuvhubs numuvhubs16 numuvhubs8 ");
		seq_puts(file,
			 "numuvhubs4 numuvhubs2 numuvhubs1 dto snacks retries ");
		seq_puts(file,
			 "rok resetp resett giveup sto bz throt disable ");
		seq_puts(file,
			 "enable wars warshw warwaits enters ipidis plugged ");
		seq_puts(file,
			 "ipiover glim cong swack recv rtime all one mult ");
		seq_puts(file, "none retry canc nocan reset rcan\n");
	}
	if (cpu < num_possible_cpus() && cpu_online(cpu)) {
		bcp = &per_cpu(bau_control, cpu);
		if (bcp->nobau) {
			seq_printf(file, "cpu %d bau disabled\n", cpu);
			return 0;
		}
		stat = bcp->statp;

		seq_printf(file,
			"cpu %d %d %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld ",
			   cpu, bcp->nobau, stat->s_requestor,
			   cycles_2_us(stat->s_time),
			   stat->s_ntargself, stat->s_ntarglocals,
			   stat->s_ntargremotes, stat->s_ntargcpu,
			   stat->s_ntarglocaluvhub, stat->s_ntargremoteuvhub,
			   stat->s_ntarguvhub, stat->s_ntarguvhub16);
		seq_printf(file, "%ld %ld %ld %ld %ld %ld ",
			   stat->s_ntarguvhub8, stat->s_ntarguvhub4,
			   stat->s_ntarguvhub2, stat->s_ntarguvhub1,
			   stat->s_dtimeout, stat->s_strongnacks);
		seq_printf(file, "%ld %ld %ld %ld %ld %ld %ld %ld ",
			   stat->s_retry_messages, stat->s_retriesok,
			   stat->s_resets_plug, stat->s_resets_timeout,
			   stat->s_giveup, stat->s_stimeout,
			   stat->s_busy, stat->s_throttles);
		seq_printf(file, "%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld ",
			   stat->s_bau_disabled, stat->s_bau_reenabled,
			   stat->s_uv2_wars, stat->s_uv2_wars_hw,
			   stat->s_uv2_war_waits, stat->s_enters,
			   stat->s_ipifordisabled, stat->s_plugged,
			   stat->s_overipilimit, stat->s_giveuplimit,
			   stat->s_congested);


		seq_printf(file,
			"%lx %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld\n",
			   read_gmmr_sw_ack(uv_cpu_to_pnode(cpu)),
			   stat->d_requestee, cycles_2_us(stat->d_time),
			   stat->d_alltlb, stat->d_onetlb, stat->d_multmsg,
			   stat->d_nomsg, stat->d_retries, stat->d_canceled,
			   stat->d_nocanceled, stat->d_resets,
			   stat->d_rcanceled);
	}
	return 0;
}
