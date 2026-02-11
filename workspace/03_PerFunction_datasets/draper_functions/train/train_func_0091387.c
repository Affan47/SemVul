actstar (sc, st, istar)

struct StarCat *sc;
struct Star *st;
int istar;
{
    int nbr;
    long offset;
    char dsgn;
    char line[256];
    int irh,irm,idd,idm;
    double rs, ds, bvmag;


    if (sc == NULL)
	return (1);


    if (sc->ifcat == NULL)
	return (2);


    if (istar > sc->nstars) {
	fprintf (stderr, "ACTSTAR:  %d  > %d is not in catalog\n",
		 istar, sc->nstars);
	return (3);
	}


    if (istar > 0) {
	offset = (istar - 1) * sc->nbent;
	if (fseek (sc->ifcat, offset, SEEK_SET))
	    return (4);
	}


    if ((nbr = fread (line, sc->nbent, 1, sc->ifcat)) > sc->nbent) {
	fprintf (stderr, "ACTSTAR:  %d / %d bytes read from %s\n",
		 nbr, sc->nbent, sc->isfil);
	return (5);
	}

    st->num = (double) istar;


    irh = atoi (line);
    irm = atoi (line+3);
    rs = atof (line+6);
    dsgn = line[14];
    idd = atoi (line+15);
    idm = atoi (line+18);
    ds = atof (line+21);


    st->ra = hrdeg ((double)irh + ((double)irm)/60.0 + rs / 3600.0);
    st->dec = (double) idd + ((double)idm) / 60.0 + ds / 3600.0;
    if (dsgn == '-') st->dec = -st->dec;


    st->rapm = hrdeg (atof (line+28)) / 3600.0;
    st->decpm = atof (line+36) / 3600.0;


    st->xmag[0] = atof (line+75);
    st->xmag[1] = atof (line+68);
    st->xmag[2] = atof (line+82);


    bvmag = st->xmag[2];
    bv2sp (&bvmag, 0.0, 0.0, st->isp);

    return (0);
}
