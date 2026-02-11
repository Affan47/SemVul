undo_rename_cancel(const nstring &from, const nstring &to)
{
    trace(("undo_rename_cancel(\"%s\", \"%s\")\n{\n",
	from.c_str(), to.c_str()));
    undo_item_rename dummy(from, to);
    for (jobs_t::iterator it = jobs.begin(); it != jobs.end(); ++it)
    {
	undo_item *ip = *it;

	undo_item_rename *irp = dynamic_cast<undo_item_rename *>(ip);
	if (irp && *irp == dummy)
	{
	    jobs.erase(it);
	    trace(("}\n"));
	    return;
	}
    }


    this_is_a_bug();
    trace(("}\n"));
}
