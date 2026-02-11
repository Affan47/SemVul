update_hv(AtmosModel & atms, const AerosolConcentration & aerocon)
{
    xps = original_xps;
    xpp = original_xpp;

    float uwus;
    float uo3us;

    if (xps <= 0) {
	xps = 0;
	uwus = 1.424f;
	uo3us = 0.344f;
    }
    else if (atms.idatm != 8)
	pressure(atms, atms.uw, atms.uo3);
    else
	pressure(atms, uwus, uo3us);

    if (xpp <= 0) {

	palt = 0;
	pps = atms.p[0];
	idatmp = 0;
	taer55p = 0;
	puw = 0;
    }
    else if (xpp >= 100) {

	palt = 1000;
	pps = 0;
	taer55p = aerocon.taer55;
	puw = 0;
	ftray = 1;
	idatmp = 4;
    }
    else {


	puw = original_puw;
	puo3 = original_puo3;

	if (puw < 0) {
	    presplane(atms);
	    idatmp = 2;

	    if (atms.idatm == 8) {
		puwus = puw;
		puo3us = puo3;
		puw *= atms.uw / uwus;
		puo3 *= atms.uo3 / uo3us;
		idatmp = 8;
	    }
	}
	else {
	    presplane(atms);
	    idatmp = 8;
	}

	palt = plane_sim.zpl[33] - atms.z[0];
	pps = plane_sim.ppl[33];
	taer55p = original_taer55p;

	if ((taer55p > 0) || ((aerocon.taer55 - taer55p) < 1e-03)) {

	    taer55p = (float)(aerocon.taer55 * (1 - exp(-palt / 2)));
	}
	else {

	    double sham = exp(-palt / 4);
	    double sha = 1 - (taer55p / aerocon.taer55);

	    if (sha >= sham)
		taer55p = (float)(aerocon.taer55 * (1 - exp(-palt / 4)));
	    else {
		sha = -palt / log(sha);
		taer55p = (float)(aerocon.taer55 * (1 - exp(-palt / sha)));
	    }
	}
    }
}
