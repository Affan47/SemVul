get_older(const nstring &filename)
{
    trace(("project_file_roll_forward::get_older(%s)\n{\n", filename.c_str()));
    assert(!filename_to_uuid.empty());
    nstring uuid(filename_to_uuid.query(filename));
    if (!uuid)
    {
	trace(("return NULL;\n"));
	trace(("}\n"));
	return 0;
    }
    file_event_list::pointer felp = uuid_to_felp.get(uuid);
    if (!felp || felp->empty())
    {
	trace(("return NULL;\n"));
	trace(("}\n"));
	return 0;
    }
    file_event *result = 0;
    for (size_t j = felp->size(); j > 0; --j)
    {


	file_event *fep = felp->get(j - 1);
	time_t when = change_completion_timestamp(fep->get_change());
	if (when < stp_time)
	{
	    result = fep;
	    break;
	}
    }
    trace(("return %08lX (%08lX)\n", (long)result, (long)result->get_src()));
    trace(("}\n"));
    return result;
}
