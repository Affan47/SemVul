name()
{
    trace(("input_crlf_name(this = %08lX)\n", (long)this));
    if (!line_number)
	return deeper->name();
    if (!name_cache)
    {
	name_cache =
	    nstring::format("%s: %ld", deeper->name().c_str(), line_number);
    }
    return name_cache;
}
