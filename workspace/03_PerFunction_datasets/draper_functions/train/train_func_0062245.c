require(String name, ErrorHandler *errh)
{
# ifdef HAVE_DYNAMIC_LINKING
    if (!click_has_provision(name.c_str()))
	clickdl_load_requirement(name, _archive, errh);
# endif
    if (!click_has_provision(name.c_str()))
	errh->error("requirement '%s' not available", name.c_str());
}
