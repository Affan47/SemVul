icalcluster_add_component(icalcluster *impl, icalcomponent* child) {

	icalerror_check_arg_re((impl!=0),"cluster", ICAL_BADARG_ERROR);
	icalerror_check_arg_re((child!=0),"child",ICAL_BADARG_ERROR);

	icalcomponent_add_component(impl->data, child);
	icalcluster_mark(impl);

	return ICAL_NO_ERROR;
}
