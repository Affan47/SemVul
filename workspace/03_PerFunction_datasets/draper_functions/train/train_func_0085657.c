setup_symbol_storage (Dsymbol *dsym, tree decl, bool public_p)
{
  Declaration *rd = dsym->isDeclaration();

  if (public_p
      || (TREE_CODE (decl) == VAR_DECL && (rd && rd->isDataseg()))
      || (TREE_CODE (decl) == FUNCTION_DECL))
    {
      bool local_p = output_module_p (dsym->getModule());
      Dsymbol *sym = dsym->toParent();

      while (sym)
	{
	  TemplateInstance *ti = sym->isTemplateInstance();
	  if (ti)
	    {
	      D_DECL_ONE_ONLY (decl) = 1;
	      D_DECL_IS_TEMPLATE (decl) = 1;
	      local_p = flag_emit_templates != TEnone
		&& output_module_p (ti->instantiatingModule);
	      break;
	    }
	  sym = sym->toParent();
	}

      VarDeclaration *vd = rd ? rd->isVarDeclaration() : NULL;
      if (vd != NULL)
	{
	  if (vd->storage_class & STCextern)
	    local_p = false;

	  if (vd->isDataseg() && vd->isThreadlocal())
	    DECL_TLS_MODEL (decl) = decl_default_tls_model (decl);
	}

      if (rd && rd->storage_class & STCcomdat)
	D_DECL_ONE_ONLY (decl) = 1;

      if (local_p)
	{
	  DECL_EXTERNAL (decl) = 0;
	  TREE_STATIC (decl) = 1;
	}
      else
	{
	  DECL_EXTERNAL (decl) = 1;
	  TREE_STATIC (decl) = 0;
	}


      FuncDeclaration *fd = rd ? rd->isFuncDeclaration() : NULL;
      if (public_p || !fd || !fd->isNested())
	TREE_PUBLIC (decl) = 1;

      if (D_DECL_ONE_ONLY (decl))
	d_comdat_linkage (decl);
    }
  else
    {
      TREE_STATIC (decl) = 0;
      DECL_EXTERNAL (decl) = 0;
      TREE_PUBLIC (decl) = 0;
    }

  if (rd && rd->userAttributes)
    decl_attributes (&decl, build_attributes (rd->userAttributes), 0);
  else if (DECL_ATTRIBUTES (decl) != NULL)
    decl_attributes (&decl, DECL_ATTRIBUTES (decl), 0);
}
