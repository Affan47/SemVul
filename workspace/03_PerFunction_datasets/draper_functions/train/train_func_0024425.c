merge_languagenames(languagenames names, languagenames name_list)
{
    languagenames res=name_list;
    {
	languagenames kc_fe_selvar_1 =  names ;

	while(
		kc_fe_selvar_1->prod_sel() == sel_Conslanguagenames
	    ) {
	    ID kc_selvar_0_1 = kc_fe_selvar_1->ID_1;
	    {
		{
		    if ((kc_selvar_0_1->prod_sel() == sel_Id)) {
			const ID id = kc_selvar_0_1;
			const uniqID u_id = phylum_cast<const impl_ID_Id*>(kc_selvar_0_1)->uniqID_1;

			if(u_id->type->eq(ITUnknown())) {
			    res=Conslanguagenames(id,res);
			    u_id->type=ITLanguageName(
				mkinteger(res->length()-1));
			}

		    } else
		    { }
		}

	    }
	    kc_fe_selvar_1 = kc_fe_selvar_1->languagenames_1;

	}
    }
    return res;

}
