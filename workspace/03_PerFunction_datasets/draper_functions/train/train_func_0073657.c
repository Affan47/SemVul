server_root_required(server_ty *sp, const char *caption)
{
    int             root_required;

    assert(sp);
    assert(caption);
    root_required = !sp->np->get_is_rooted();
    if (root_required)
	server_error(sp, "%s: must send Root request first", caption);
    return root_required;
}
