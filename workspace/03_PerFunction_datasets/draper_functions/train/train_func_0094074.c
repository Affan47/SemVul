organize_fp_lookup(struct Colors *colors, int mod)
{
    int i;
    DCELL val;
    struct _Color_Info_ *cp;
    struct _Color_Rule_ *rule;

    if (mod)
	cp = &colors->modular;
    else
	cp = &colors->fixed;


    if (cp->lookup.active || cp->fp_lookup.active)
	return 1;
    if (cp->n_rules == 0)
	return 1;

    cp->fp_lookup.vals = (DCELL *)
	G_calloc(cp->n_rules * 2, sizeof(DCELL));

    cp->fp_lookup.rules = (struct _Color_Rule_ **)
	G_calloc(cp->n_rules * 2, sizeof(struct _Color_Rule_ *));


    i = 0;


    for (rule = cp->rules; rule->next; rule = rule->next) ;

    for (; rule; rule = rule->prev) {

	if (i == 0 || rule->low.value != cp->fp_lookup.vals[i - 1])
	    cp->fp_lookup.vals[i++] = rule->low.value;
	cp->fp_lookup.vals[i++] = rule->high.value;
    }
    cp->fp_lookup.nalloc = i;


    qsort((char *)cp->fp_lookup.vals, cp->fp_lookup.nalloc,
	  sizeof(DCELL), &double_comp);


    for (i = 0; i < cp->fp_lookup.nalloc - 1; i++) {
	val = (cp->fp_lookup.vals[i] + cp->fp_lookup.vals[i + 1]) / 2.;


	for (rule = cp->rules; rule; rule = rule->next)
	    if (rule->low.value <= val && val <= rule->high.value)
		break;


	cp->fp_lookup.rules[i] = rule;
    }
    cp->fp_lookup.active = 1;

    return 0;
}
