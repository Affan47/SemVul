pvalIncludeGetTimeConstraints( pval *p, char **hour_range, char **dom_range, char **dow_range, char **month_range )
{
	if (!pvalCheckType(p, "pvalIncludeGetTimeConstraints", PV_WORD))
		return;
	if (p->u2.arglist) {
		*hour_range = p->u2.arglist->u1.str;
		*dom_range = p->u2.arglist->next->u1.str;
		*dow_range = p->u2.arglist->next->next->u1.str;
		*month_range = p->u2.arglist->next->next->next->u1.str;
	} else {
		*hour_range = 0;
		*dom_range = 0;
		*dow_range = 0;
		*month_range = 0;
	}
}
