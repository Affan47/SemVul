ifline(time_t deltasec, time_t deltatic, time_t hz,
				int ncpu, struct osrel *osr, char *tstamp)
{
	static int	sampcnt = 0;
	register int	i, j, nvalid, nrif;
	double		ip, op, ib, ob, ic, oc, im;
	struct ifstat 	*cur, *pre;

	if ( !(nrif = getcset("ifstat", (void **)&cur, (void **)&pre)) )
		return(0);

	sampcnt++;

	for (i=0, j=0, nvalid=0; i < nrif; i++, j=i)
	{
		if ( (cur+i)->name[0] == 0 )
			break;


		if ( strcmp( (cur+i)->name, (pre+j)->name) != 0)
		{

			for (j=0; j < nrif; j++)
			{
				if ( (pre+j)->name[0] == 0 )
					break;

				if  ( strcmp( (cur+i)->name, (pre+j)->name) ==0)
					break;
			}

			sampcnt = 1;
		}

		ip = subtract((cur+i)->rpack,   (pre+j)->rpack);
		op = subtract((cur+i)->spack,   (pre+j)->spack);
		ib = subtract((cur+i)->rbyte,   (pre+j)->rbyte);
		ob = subtract((cur+i)->sbyte,   (pre+j)->sbyte);
		ic = subtract((cur+i)->rcompr,  (pre+j)->rcompr);
		oc = subtract((cur+i)->scompr,  (pre+j)->scompr);
		im = subtract((cur+i)->rmultic, (pre+j)->rmultic);


		if (sampcnt > 1 && !ip && !op)
			continue;

		if (nvalid)	printf("%s  ", tstamp);

		nvalid++;

		printf("%7.1lf %7.1lf %7.0lf %7.0lf %8.2lf %8.2lf %8.2lf %s\n",
			ip / deltasec,
			op / deltasec,
			ib / deltasec,
			ob / deltasec,
			ic / deltasec,
			oc / deltasec,
			im / deltasec,
			(cur+i)->name);
	}

	if (nvalid == 0)
		printf("\n");

	return(1);
}
