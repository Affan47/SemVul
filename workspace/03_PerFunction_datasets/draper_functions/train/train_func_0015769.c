getoff_ifile(ifile)
	IFILE ifile;
{
	IFILE newifile;

	if ((newifile = prev_ifile(ifile)) != NULL_IFILE)
		return (newifile);
	if ((newifile = next_ifile(ifile)) != NULL_IFILE)
		return (newifile);
	return (NULL_IFILE);
}
