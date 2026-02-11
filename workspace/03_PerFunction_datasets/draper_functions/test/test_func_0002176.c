print_group_header_rt(ulong rt_rq, void *t)
{
	int throttled;
	struct task_group_info *tgi = (struct task_group_info *)t;

	fprintf(fp, "GROUP RT PRIO_ARRAY: %lx", rt_rq + OFFSET(rt_rq_active));
	if (tgi->name)
		fprintf(fp, " <%s>", tgi->name);

	if (VALID_MEMBER(task_group_rt_bandwidth)) {
		readmem(rt_rq + OFFSET(rt_rq_rt_throttled), KVADDR,
			&throttled, sizeof(int), "rt_rq rt_throttled",
			FAULT_ON_ERROR);
		if (throttled)
			fprintf(fp, " (THROTTLED)");
	}
	fprintf(fp, "\n");
}
