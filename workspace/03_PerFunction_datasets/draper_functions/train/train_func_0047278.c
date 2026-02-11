print_constraints()
{
	char *buf = xstrdup("");

	if (opt.pn_min_cpus != NO_VAL)
		xstrfmtcat(buf, "mincpus-per-node=%d ", opt.pn_min_cpus);

	if (opt.pn_min_memory != NO_VAL)
		xstrfmtcat(buf, "mem-per-node=%dM ", opt.pn_min_memory);

	if (opt.mem_per_cpu != NO_VAL)
		xstrfmtcat(buf, "mem-per-cpu=%dM ", opt.mem_per_cpu);

	if (opt.pn_min_tmp_disk != NO_VAL)
		xstrfmtcat(buf, "tmp-per-node=%ld ", opt.pn_min_tmp_disk);

	if (opt.contiguous == true)
		xstrcat(buf, "contiguous ");

	if (opt.nodelist != NULL)
		xstrfmtcat(buf, "nodelist=%s ", opt.nodelist);

	if (opt.exc_nodes != NULL)
		xstrfmtcat(buf, "exclude=%s ", opt.exc_nodes);

	if (opt.constraints != NULL)
		xstrfmtcat(buf, "constraints=`%s' ", opt.constraints);

	return buf;
}
