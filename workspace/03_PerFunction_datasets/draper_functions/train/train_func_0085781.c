zen_no_ref(struct posdata *pdat, struct trigdata *tdat)
{
    float cz;

    localtrig(pdat, tdat);
    cz = tdat->sd * tdat->sl + tdat->cd * tdat->cl * tdat->ch;


    if (fabs(cz) > 1.0) {
	if (cz >= 0.0)
	    cz = 1.0;
	else
	    cz = -1.0;
    }

    pdat->zenetr = acos(cz) * degrad;


    if (pdat->zenetr > 99.0)
	pdat->zenetr = 99.0;

    pdat->elevetr = 90.0 - pdat->zenetr;
}
