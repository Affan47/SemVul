f_do_subphylum
#ifdef KC_USE_PROTOTYPES
(arguments a, INT i, int a_i)
#else
(a, i, a_i) arguments a;
INT i;
int a_i;
#endif
#line 1604 "../util.k"
{{
#line 1603 "../util.k"
arguments kc_selvar_0_1 = a;
#line 1603 "../util.k"

assert_arguments(kc_selvar_0_1, "with_expression (1)");

#line 2132 "util.c"
		if (( kc_selvar_0_1->prod_sel == sel_Consarguments)) {
#line 1606 "../util.k"
		ID a_a =  kc_selvar_0_1->u.Consarguments.ID_1;
#line 1606 "../util.k"
		arguments a_as =  kc_selvar_0_1->u.Consarguments.arguments_1;
#line 1606 "../util.k"

		{
#line 1607 "../util.k"
INT kc_selvar_1_1 =
 i
;
#line 1607 "../util.k"

assert_INT(kc_selvar_1_1, "with_expression (1)");

#line 2149 "util.c"
		if (( kc_selvar_1_1->prod_sel == sel_Int)) {
#line 1608 "../util.k"
		int ii =  kc_selvar_1_1->u.Int.int_1;
#line 1608 "../util.k"

				if (ii == a_i) {
					return a_a;
				} else {
					return f_do_subphylum( a_as, i, a_i - 1 );
}
#line 2160 "util.c"
		} else
{ kc_no_default_in_with( "f_do_subphylum", __LINE__, __FILE__ );
   return (ID)0; }
}
#line 1613 "../util.k"

#line 2167 "util.c"
		} else
		if (( kc_selvar_0_1->prod_sel == sel_Nilarguments)) {
#line 1605 "../util.k"
  return f_emptyId();
#line 2172 "util.c"
		} else
{ kc_no_default_in_with( "f_do_subphylum", __LINE__, __FILE__ );
   return (ID)0; }
}

#line 1613 "../util.k"
}
