v_do_check_dollarvar_in_operators(INT i, operators o, ID p)
{{
	operators kc_selvar_0_1 = phylum_cast<operators>(o);
	if ((kc_selvar_0_1->prod_sel() == sel_Consoperators)) {
	    const ID o_o = (kc_selvar_0_1)->ID_1;
	    const operators o_os = (kc_selvar_0_1)->operators_1;

	    ID phy = f_subphylumofoperator( o_o, i );
	    if (phy->eq(f_emptyId())) {
		v_report(NonFatal( FileLine( i->file, i->line ),
			Problem1S1INT1S1ID( "illegal dollar variable", i,
			    "not that many subterms in operator", o_o )));
	    } else if (! p->eq( phy )) {
		v_report(NonFatal( FileLine( i->file, i->line ),
			Problem1S1INT1S1ID1S1ID( " type mismatch for dollar varariable:", i,
			    "; old type", p, "; new type", phy )));
	    }
	    v_do_check_dollarvar_in_operators( i, o_os, p );

	} else
	    if ((kc_selvar_0_1->prod_sel() == sel_Niloperators)) {

	    	} else
	    kc_no_default_in_with( "v_do_check_dollarvar_in_operators", __LINE__, __FILE__ );
    }

}
