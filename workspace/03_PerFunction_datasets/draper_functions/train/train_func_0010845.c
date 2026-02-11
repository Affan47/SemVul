get_pi(struct args *args) {
	struct prog_info *pi;
	struct data_list *warnings;

	pi = (struct prog_info *)calloc(1, sizeof(struct prog_info));
	if(!pi)
		return(NULL);
	memset(pi, 0, sizeof(struct prog_info));
	pi->args = args;
	pi->device = get_device(pi,NULL);
	if(GET_ARG(args, ARG_LISTFILE) == NULL) {
		pi->list_on = False;
	} else {
		pi->list_on = True;
	}
	if(GET_ARG(args, ARG_MAPFILE) == NULL) {
		pi->map_on = False;
	} else {
		pi->map_on = True;
	}
	for(warnings = GET_ARG(args, ARG_WARNINGS); warnings; warnings = warnings->next) {
		if(!nocase_strcmp(warnings->data, "NoRegDef"))
			pi->NoRegDef = 1;
	}
	pi->segment = SEGMENT_CODE;
	pi->dseg_addr = pi->device->ram_start;
	pi->max_errors = atoi(GET_ARG(args, ARG_MAX_ERRORS));
	pi->pass=PASS_1;
	pi->time=time(NULL);
	return(pi);
}
