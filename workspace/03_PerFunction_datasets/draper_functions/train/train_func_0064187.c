f_operatorofpatternrepresentation
#ifdef KC_USE_PROTOTYPES
(patternrepresentation a_patternrepresentation)
#else
(a_patternrepresentation) patternrepresentation a_patternrepresentation;
#endif
#line 737 "../gutil.k"
{
    {
#line 738 "../gutil.k"
patternrepresentation kc_selvar_0_1 =
 a_patternrepresentation
;
#line 738 "../gutil.k"

assert_patternrepresentation(kc_selvar_0_1, "with_expression (1)");

#line 2125 "gutil.c"
		if (( kc_selvar_0_1->prod_sel == sel_Conspatternrepresentation)) {
#line 742 "../gutil.k"
		elem_patternrepresentation e =  kc_selvar_0_1->u.Conspatternrepresentation.elem_patternrepresentation_1;
#line 742 "../gutil.k"

	    return f_operatorofelem_patternrepresentation( e );

#line 2133 "gutil.c"
		} else
		if (( kc_selvar_0_1->prod_sel == sel_Nilpatternrepresentation)) {
#line 739 "../gutil.k"

	    return f_emptyId();

#line 2140 "gutil.c"
		} else
{ kc_no_default_in_with( "f_operatorofpatternrepresentation", __LINE__, __FILE__ );
   return (ID)0; }
}
#line 744 "../gutil.k"

#line 744 "../gutil.k"
}
