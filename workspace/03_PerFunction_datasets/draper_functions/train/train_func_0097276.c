print_info_set_breaks (PrintInformation *pi,
		       GnmPageBreaks    *breaks)
{
	GnmPageBreaks **target;

	g_return_if_fail (pi != NULL);

	target = breaks->is_vert ? &pi->page_breaks.v : &pi->page_breaks.h;

	if (*target == breaks)
		return;

	gnm_page_breaks_free (*target);
	*target = breaks;
}
