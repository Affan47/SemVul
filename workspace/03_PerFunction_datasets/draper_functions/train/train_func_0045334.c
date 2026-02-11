f_outmost_nl_preds_in_paths
#ifdef KC_USE_PROTOTYPES
(paths p)
#else
(p) paths p;
#endif
#line 826 "../gutil.k"
{
    {
#line 827 "../gutil.k"
paths kc_selvar_0_1 =
 p
;
#line 827 "../gutil.k"

assert_paths(kc_selvar_0_1, "with_expression (1)");

#line 2561 "gutil.c"
		if (( kc_selvar_0_1->prod_sel == sel_Conspaths) && ( kc_selvar_0_1->u.Conspaths.path_1->prod_sel == sel_Conspath)) {
#line 830 "../gutil.k"
		paths r_p =  kc_selvar_0_1->u.Conspaths.paths_1;
#line 830 "../gutil.k"

	    return f_outmost_nl_preds_in_paths( r_p );

#line 2569 "gutil.c"
		} else
		if (( kc_selvar_0_1->prod_sel == sel_Conspaths) && ( kc_selvar_0_1->u.Conspaths.path_1->prod_sel == sel_Nilpath)) {
#line 829 "../gutil.k"
 return True;
#line 2574 "gutil.c"
		} else
		if (( kc_selvar_0_1->prod_sel == sel_Nilpaths)) {
#line 828 "../gutil.k"
 return False;
#line 2579 "gutil.c"
		} else
{ kc_no_default_in_with( "f_outmost_nl_preds_in_paths", __LINE__, __FILE__ );
   return (boolean)0; }
}
#line 832 "../gutil.k"

#line 832 "../gutil.k"
}
