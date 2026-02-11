rewrite(rview kc_current_view_base)
{
    casestring l_casestring_1 =
	casestring_1->rewrite(kc_current_view_base);
    casestring l_casestring_2 =
	casestring_2->rewrite(kc_current_view_base);
    casestring l_casestring_3 =
	casestring_3->rewrite(kc_current_view_base);
    casestring l_casestring_4 =
	casestring_4->rewrite(kc_current_view_base);
    casestring l_casestring_5 =
	casestring_5->rewrite(kc_current_view_base);
    if ((l_casestring_1 == casestring_1) &&  (l_casestring_2 == casestring_2) &&  (l_casestring_3 == casestring_3) &&  (l_casestring_4 == casestring_4) &&  (l_casestring_5 == casestring_5))
	return this;
    else {
	impl_problem_Problem5* kc_result= Problem5(l_casestring_1, l_casestring_2, l_casestring_3, l_casestring_4, l_casestring_5);
	kc_result->rewrite_members(this);
	return kc_result;
    }
}
