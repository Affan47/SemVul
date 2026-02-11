setvimoswcsdeg(vimoswcs, new)
struct	WorldCoor *vimoswcs;
int	new;
{
    int old;

    if (novimoswcs (vimoswcs))
	return (0);
    old = vimoswcs->degout;
    vimoswcs->degout = new;
    if (new == 1 && old == 0 && vimoswcs->ndec == 3)
	vimoswcs->ndec = 6;
    if (new == 0 && old == 1 && vimoswcs->ndec == 5)
	vimoswcs->ndec = 3;
    return(old);
}
