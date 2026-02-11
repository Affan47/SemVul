subst_name
#ifdef KC_USE_PROTOTYPES
(ID n, casestring oldname, casestring newname)
#else
(n, oldname, newname) ID n;
casestring oldname;
casestring newname;
#endif
#line 575 "../parse.k"
{{
#line 574 "../parse.k"
ID kc_selvar_0_1 = n;
#line 574 "../parse.k"

assert_ID(kc_selvar_0_1, "with_expression (1)");

#line 1814 "parse.c"
		if (( kc_selvar_0_1->prod_sel == sel_Id) && ( kc_selvar_0_1->u.Id.uniqID_1->prod_sel == sel_Str)) {
#line 576 "../parse.k"
		casestring s =  kc_selvar_0_1->u.Id.uniqID_1->u.Str.casestring_1;
#line 576 "../parse.k"

		if (eq_casestring( s, oldname)) {
			ID tmp = Id(Str(newname));
			tmp->file = n->file;
			tmp->line = n->line;
			return tmp;
		} else {
			return n;
		}

#line 1829 "parse.c"
		} else
{ kc_no_default_in_with( "subst_name", __LINE__, __FILE__ );
   return (ID)0; }
}

#line 586 "../parse.k"
}
