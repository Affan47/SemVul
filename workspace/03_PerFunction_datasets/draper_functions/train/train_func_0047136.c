sample_color(struct pine *ps, struct variable *v)
{
    COLOR_PAIR *cp = NULL;
    char *pvalefg, *pvalebg;
    char *pvalmfg, *pvalmbg;

    pvalefg = PVAL(v, ew);
    pvalebg = PVAL(v+1, ew);
    pvalmfg = PVAL(v, Main);
    pvalmbg = PVAL(v+1, Main);
    if(v && color_holding_var(ps, v) &&
       srchstr(v->name, "-foreground-color")){
	if(pvalefg && pvalefg[0] && pvalebg && pvalebg[0])
	  cp = new_color_pair(pvalefg, pvalebg);
	else if(ew == Post && pvalmfg && pvalmfg[0] && pvalmbg && pvalmbg[0])
	  cp = new_color_pair(pvalmfg, pvalmbg);
	else if(v->global_val.p && v->global_val.p[0] &&
	        (v+1)->global_val.p && (v+1)->global_val.p[0])
	  cp = new_color_pair(v->global_val.p, (v+1)->global_val.p);
    }

    return(cp);
}
