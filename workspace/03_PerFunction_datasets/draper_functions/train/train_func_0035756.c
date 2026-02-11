rewrite_CexpressionSQ_elem
#ifdef KC_USE_PROTOTYPES
(CexpressionSQ_elem kc_p, rview kc_current_view)
#else
(kc_p, kc_current_view) CexpressionSQ_elem kc_p; rview kc_current_view;
#endif
{

	assert_CexpressionSQ_elem( kc_p, "kc_p" );
	switch((int)kc_current_view) {
	default:
	case (int)base_rview: {
		switch((int)kc_p->prod_sel) {
		case (int)sel_CExpressionSQPart: {
		casestring casestring_1 = rewrite_casestring(kc_p->u.CExpressionSQPart.casestring_1, kc_current_view);
		if ((casestring_1 == kc_p->u.CExpressionSQPart.casestring_1))
			return kc_p;
		else
			return CExpressionSQPart(casestring_1);
		}
		case (int)sel_CExpressionSQNl: {
		int int_1 = rewrite_int(kc_p->u.CExpressionSQNl.int_1, kc_current_view);
		if ((int_1 == kc_p->u.CExpressionSQNl.int_1))
			return kc_p;
		else
			return CExpressionSQNl(int_1);
		}
		default: return kc_p;}
	}
	}
}
