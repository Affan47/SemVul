Clp_SetOptionChar(Clp_Parser *clp, int c, int type)
{
    int i, j, long1pos, long1neg;
    int old = Clp_OptionChar(clp, c);
    Clp_Internal *cli = clp->internal;

    if (type != Clp_NotOption && type != Clp_Short && type != Clp_Long
	&& type != Clp_ShortNegated && type != Clp_LongNegated
	&& type != Clp_LongImplicit && type != (Clp_Short | Clp_Long)
	&& type != (Clp_ShortNegated | Clp_LongNegated))
	return -1;
    if (c < 0 || c >= (cli->utf8 ? 0x110000 : 256))
	return -1;

    if (c == 0)
	cli->noclass = 0;
    for (i = 0; i < cli->noclass; ++i)
	if (cli->oclass[i].c == c)
	    break;
    if (i == Clp_OclassSize)
	return -1;

    cli->oclass[i].c = c;
    cli->oclass[i].type = type;
    if (cli->noclass == i)
	cli->noclass = i + 1;

    long1pos = long1neg = 0;
    for (i = 0; i < cli->noclass; ++i) {
	if ((cli->oclass[i].type & Clp_Short)
	    && (cli->oclass[i].type & Clp_Long))
	    long1pos = 1;
	if ((cli->oclass[i].type & Clp_ShortNegated)
	    && (cli->oclass[i].type & Clp_LongNegated))
	    long1neg = 1;
    }

    if (long1pos != cli->long1pos || long1neg != cli->long1neg) {

	cli->long1pos = long1pos;
	cli->long1neg = long1neg;
	for (i = 0; i < cli->nopt; ++i) {
	    cli->iopt[i].lmmpos = cli->iopt[i].lmmneg = 1;
	    cli->iopt[i].lmmpos_short = cli->iopt[i].lmmneg_short = 0;
	    for (j = 0; j < cli->nopt; ++j)
		compare_options(clp, &cli->opt[i], &cli->iopt[i],
				&cli->opt[j], &cli->iopt[j]);
	}
    }

    return old;
}
