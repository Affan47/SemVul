equal_path(path a_path1, path a_path2)
{
    path r_a_path1=a_path1->reverse(), r_a_path2=a_path2->reverse();
    tribool ret;
    bool breakforeach = false;
    {
	path kc_fe_selvar_1 =  r_a_path1;
	path kc_fe_selvar_2 =  r_a_path2;

	while(
		kc_fe_selvar_1->prod_sel() == sel_Conspath
		&& kc_fe_selvar_2->prod_sel() == sel_Conspath
	    ) {
	    integer kc_selvar_0_1 = kc_fe_selvar_1->integer_1;
	    integer kc_selvar_0_2 = kc_fe_selvar_2->integer_1;
	    {
		{
		    {
			const integer i1 = kc_selvar_0_1;
			const integer i2 = kc_selvar_0_2;

			if (!breakforeach) {
			    if ( i1->value < i2->value )
			    ret = Smaller(), breakforeach = true;
			    else if (i1->value > i2->value )
			    ret = Bigger(), breakforeach = true;
			}

		    }
		}

	    }
	    kc_fe_selvar_1 = kc_fe_selvar_1->path_1;
	    kc_fe_selvar_2 = kc_fe_selvar_2->path_1;

	}
	{
	    {
		{
		    const path re1 = kc_fe_selvar_1;
		    const path re2 = kc_fe_selvar_2;
		    {
			path kc_selvar_1_1 = phylum_cast<path>(re1);
			path kc_selvar_1_2 = phylum_cast<path>(re2);
			if ((kc_selvar_1_1->prod_sel() == sel_Nilpath) && (kc_selvar_1_2->prod_sel() == sel_Conspath)) {
			    ret = breakforeach ? ret : Bigger();
			    	} else
			    if ((kc_selvar_1_1->prod_sel() == sel_Conspath) && (kc_selvar_1_2->prod_sel() == sel_Nilpath)) {
			    ret = breakforeach ? ret : Smaller();
			    	} else
			    if ((kc_selvar_1_1->prod_sel() == sel_Nilpath) && (kc_selvar_1_2->prod_sel() == sel_Nilpath)) {
			    ret = breakforeach ? ret : Equal();
			    	} else
			{ kc_no_default_in_with( "equal_path", __LINE__, __FILE__ );
			    return static_cast<tribool>(0); }
		    }

		}
	    }

	}
    }
    r_a_path1->freelist(); r_a_path2->freelist();
    return ret;

}
