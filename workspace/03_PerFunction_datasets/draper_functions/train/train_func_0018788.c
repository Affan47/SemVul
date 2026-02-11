find_option (const char letter_)
{
    trace_with_mask ("CmdLineOpts::find_option(char)", CMDLINEOPTS);

    OptionSet::iterator i;

    for (i = m_opts_set.begin (); i != m_opts_set.end (); i++)
    {
		if (i->m_short_name == letter_)
			return &(*i);
    }
    return (NULL);
}
