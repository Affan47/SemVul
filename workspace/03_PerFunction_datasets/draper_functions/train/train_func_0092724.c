sampleexc_color(struct pine *ps, struct variable *v)
{
    COLOR_PAIR *cp = NULL;
    char *pvalfg, *pvalbg;

    pvalfg = PVAL(v, Post);
    pvalbg = PVAL(v+1, Post);
    if(v && color_holding_var(ps, v) &&
       srchstr(v->name, "-foreground-color") &&
       pvalfg && pvalfg[0] && pvalbg && pvalbg[0])
	cp = new_color_pair(pvalfg, pvalbg);

    return(cp);
}
