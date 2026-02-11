set_MSS5(lsat_data * lsat)
{
    int i, j;
    double julian, *lmax, *lmin;


    double Lmax[][4] = {
	{240., 170., 150., 127.},
	{268., 179., 159., 123.},
	{268., 179., 148., 123.}
    };
    double Lmin[][4] = {
	{4., 3., 4., 2.},
	{3., 3., 4., 3.},
	{3., 3., 5., 3.}
    };


    double esun[] = { 1824., 1570., 1249., 853.4 };

    julian = julian_char(lsat->creation);
    if (julian < julian_char("1984-04-06"))
	i = 0;
    else if (julian < julian_char("1984-11-08"))
	i = 1;
    else
	i = 2;

    lmax = Lmax[i];
    lmin = Lmin[i];

    lsat->number = 5;
    sensor_MSS(lsat);

    lsat->dist_es = earth_sun(lsat->date);

    for (i = 0; i < lsat->bands; i++) {
	j = lsat->band[i].number - 1;
	lsat->band[i].esun = *(esun + j);
	lsat->band[i].lmax = *(lmax + j);
	lsat->band[i].lmin = *(lmin + j);
    }
    G_debug(1, "Landsat-5 MSS");
    return;
}
