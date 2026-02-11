rem_from_filter()
{
const	char *p;

	while ((p=NextLine()) && *p == '\n')
		;
	if (!p)	return (0);

	if (strncmp(p, "From ", 5))
	{
		current_line=p;
		return ( no_from_filter_header() );
	}
	p=NextLine();
	if (!p)	return (p);
	current_line=p;
	rem_from_filter_header_ptr= &no_from_filter_header;
	return ( rem_from_filter_header() );
}
