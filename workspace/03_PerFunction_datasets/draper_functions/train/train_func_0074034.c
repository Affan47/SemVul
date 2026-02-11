parse_date(char *date, int &year, int &month, int &day)
{
	HtConfiguration* config= HtConfiguration::config();
    int		mm = -1, dd = -1, yy = -1, t;
    String	scandate = date;

    for (char *s = scandate.get(); *s; s++)
	if (ispunct(*s))
	    *s = ' ';

    if (config->Boolean("iso_8601"))
    {

	sscanf(scandate.get(), "%d%d%d", &yy, &mm, &dd);
    }
    else
    {


	sscanf(scandate.get(), "%d%d%d", &mm, &dd, &yy);
	if (mm > 31 && dd <= 12 && yy <= 31)
	{

	    t = mm; mm = dd; dd = yy; yy = t;
	}
    }


    if (dd > 31 && yy <= 31)
    {
	t = yy; yy = dd; dd = t;
    }
    if (mm > 31 && yy <= 31)
    {
	t = yy; yy = mm; mm = t;
    }
    if (mm > 12 && dd <= 12)
    {
	t = dd; dd = mm; mm = t;
    }
    if (yy < 0 || mm < 1 || mm > 12 || dd < 1 || dd > 31)
	return 0;

    if (yy < 70)
	yy += 2000;
    else if (yy < 1900)
	yy += 1900;
    if (verbose > 2)
	cout << "Date used (y-m-d): " << yy << '-' << mm << '-' << dd << endl;

    year = yy;
    month = mm;
    day = dd;

    return 1;
}
