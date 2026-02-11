f_typeof(path a_path)
{
    if (a_path->id->eq(f_emptyId())) {
	{
	    path kc_selvar_0_1 = phylum_cast<path>( a_path );
	    if ((kc_selvar_0_1->prod_sel() == sel_Conspath)) {
		const integer i = (kc_selvar_0_1)->integer_1;
		const path r_path = (kc_selvar_0_1)->path_1;

		return f_subphylumofoperator( r_path->op, Int( i ) );

	    } else
		if ((kc_selvar_0_1->prod_sel() == sel_Nilpath)) {

		return f_phylumofoperator( a_path->op );

	    } else
	    { kc_no_default_in_with( "f_typeof", __LINE__, __FILE__ );
		return static_cast<ID>(0); }
	}
    } else {
	return a_path->id;
    }

}
