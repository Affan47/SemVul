color_pretty_value(struct pine *ps, CONF_S *cl)
{
    char             tmp[6*MAXPATH];
    char            *p, *q;
    struct variable *v;
    int              is_index;

    tmp[0] = '\0';
    v = cl->var;

    if(v && color_holding_var(ps, v) &&
       (p=srchstr(v->name, "-foreground-color"))){

	is_index = !struncmp(v->name, "index-", 6);

	q = sampleexc_text(ps, v);
	utf8_snprintf(tmp, sizeof(tmp), "%c%.*s %sColor%*.50s %.20w%*s%.20w%.20w",
		islower((unsigned char)v->name[0])
					? toupper((unsigned char)v->name[0])
					: v->name[0],
		MIN(p-v->name-1,30), v->name+1,
		is_index ? "Symbol " : "",
		MAX(EQ_COL - COLOR_INDENT -1 - MIN(p-v->name-1,30)
			    - 6 - (is_index ? 7 : 0) - 1,0), "",
		sample_text(ps,v), *q ? SBS : 0, "", q,
		color_parenthetical(v));
    }

    tmp[sizeof(tmp)-1] = '\0';

    return(cpystr(tmp));
}
