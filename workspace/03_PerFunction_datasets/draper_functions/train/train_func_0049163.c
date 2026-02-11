prepare_base_classes(baseclass_declarations decls)
{
    {
	baseclass_declarations kc_fe_selvar_1 =  decls;

	while(
		kc_fe_selvar_1->prod_sel() == sel_Consbaseclass_declarations
	    ) {
	    baseclass_decl kc_selvar_0_1 = kc_fe_selvar_1->baseclass_decl_1;
	    {
		{
		    if ((kc_selvar_0_1->prod_sel() == sel_BaseClassDecl)) {
			const ID id = phylum_cast<const impl_baseclass_decl_BaseClassDecl*>(kc_selvar_0_1)->ID_1;
			const baseclass_list bases = phylum_cast<const impl_baseclass_decl_BaseClassDecl*>(kc_selvar_0_1)->baseclass_list_1;

			phylumdeclaration ph_decl=f_phylumdeclofid(id);
			alternative op=f_alternativeofoperator(id);
			if(ph_decl)
			ph_decl->base_classes=concat(bases, ph_decl->base_classes);
			else if(op)
			op->base_classes=concat(bases,op->base_classes);

		    } else
		    { }
		}

	    }
	    kc_fe_selvar_1 = kc_fe_selvar_1->baseclass_declarations_1;

	}
    }

}
