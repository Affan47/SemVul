print_event(struct event *event)
{

	#define N(str) ((str) ? str : "")


	if (event->type == ET_MACHINE_ID)
		return;

	if (!all_events_flag && event->type != ET_START)
		return;

	if (all_events_flag)
		printf("%-5.5s ", get_rec_type(event));


	printf("%-25.25s", N(event->name));
	if (uuid_flag)
		printf("\t%-36.36s", N(event->uuid));
	printf("\t%-11.11s\t%-35.35s", get_username(event),
			get_time_period(event));


	if (event->type == ET_RES) {
		printf("\t%-12.12s", N(event->res_type));
		printf("\t%-10.10s", N(event->reason));
		if (strcmp("cgroup", event->res_type) != 0) {
			printf("\t%s", N(event->res));
		} else {
			printf("\t%s\t%s\t%s", N(event->cgroup_class),
					N(event->cgroup_acl),
					N(event->cgroup_detail));
		}
	} else if (event->type == ET_MACHINE_ID) {
		printf("\t%s", N(event->seclevel));
	} else if (event->type == ET_AVC) {
		printf("\t%-12.12s", N(event->avc_operation));
		printf("\t%-10.10s", N(event->avc_result));
		printf("\t%s\t%s\t%s", N(event->comm), N(event->target),
				N(event->context));
	}
	printf("\n");


	if (proof_flag) {
		int first = 1;
		int i, len = sizeof(event->proof)/sizeof(event->proof[0]);
		printf("    Proof:");
		for (i = 0; i < len; i++) {
			if (event->proof[i].time) {
				printf("%s %ld.%03u:%lu",
					(first) ? "" : ",",
					event->proof[i].time,
					event->proof[i].milli,
					event->proof[i].serial);
				first = 0;
			}
		}
		printf("\n\n");
	}
}
