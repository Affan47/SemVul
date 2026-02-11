rewrite(rview kc_current_view_base)
{
    if (is_nil()) {
	return this;
    } else {
	elem_patternrepresentation l_elem_patternrepresentation_1 =
	    elem_patternrepresentation_1->rewrite(kc_current_view_base);
	patternrepresentation l_patternrepresentation_1 =
	    patternrepresentation_1->rewrite(kc_current_view_base);
	switch(kc_current_view_base) {
	    default:
	    case base_rview_enum: {
		base_rview_class& kc_current_view=static_cast<base_rview_class&>(kc_current_view_base);
		if ((l_elem_patternrepresentation_1->prod_sel() == sel_PRWildcard)) { KC_TRACE_REWRITE_MATCH(kc_current_view, "gutil.k", 706, this);
		    const patternrepresentation r = l_patternrepresentation_1;
		    patternrepresentation kc_result = r;

		    KC_TRACE_REWRITE_RESULT(kc_current_view,"gutil.k",706,kc_result);
		    return (const_cast<const impl_patternrepresentation*>(kc_result) == this) ? this : kc_result->rewrite( kc_current_view_base );

		} else
		    if ((l_elem_patternrepresentation_1->prod_sel() == sel_PRDefault)) { KC_TRACE_REWRITE_MATCH(kc_current_view, "gutil.k", 707, this);
		    const patternrepresentation r = l_patternrepresentation_1;
		    patternrepresentation kc_result = r;

		    KC_TRACE_REWRITE_RESULT(kc_current_view,"gutil.k",707,kc_result);
		    return (const_cast<const impl_patternrepresentation*>(kc_result) == this) ? this : kc_result->rewrite( kc_current_view_base );

		} else
		    break;    }
	}
	if ((l_elem_patternrepresentation_1 == elem_patternrepresentation_1) &&  (l_patternrepresentation_1 == patternrepresentation_1))
	    return this;
	else {
	    impl_patternrepresentation* kc_result= Conspatternrepresentation(l_elem_patternrepresentation_1, l_patternrepresentation_1);
	    kc_result->rewrite_members(this);
	    return kc_result;
	}   }
}
