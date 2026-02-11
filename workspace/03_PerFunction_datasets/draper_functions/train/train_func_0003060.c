pvalGotoGetTarget( pval *p, char **context, char **exten, char **label )
{
	if (!pvalCheckType(p, "pvalGotoGetTarget", PV_GOTO))
		return;
	if (p->u1.list && p->u1.list->next && p->u1.list->next->next) {
		*context = p->u1.list->u1.str;
		*exten = p->u1.list->next->u1.str;
		*label = p->u1.list->next->next->u1.str;

	} else if (p->u1.list && p->u1.list->next ) {
		*exten = p->u1.list->u1.str;
		*label = p->u1.list->next->u1.str;
		*context = 0;

	} else if (p->u1.list) {
		*label = p->u1.list->u1.str;
		*context = 0;
		*exten = 0;

	} else {
		*context = 0;
		*exten = 0;
		*label = 0;
	}
}
