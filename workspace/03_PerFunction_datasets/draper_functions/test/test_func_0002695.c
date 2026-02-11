startFunction (FuncDeclaration *decl)
{
  IRState *new_irs = new IRState();
  new_irs->parent = current_irstate;
  new_irs->func = decl;

  for (Dsymbol *p = decl->parent; p; p = p->parent)
    {
      if (p->isModule())
	{
	  new_irs->mod = p->isModule();
	  break;
	}
    }

  current_irstate = (IRState *) new_irs;
  ModuleInfo *mi = current_module_info;

  if (decl->isSharedStaticCtorDeclaration())
    mi->sharedctors.safe_push (decl);
  else if (decl->isStaticCtorDeclaration())
    mi->ctors.safe_push (decl);
  else if (decl->isSharedStaticDtorDeclaration())
    {
      VarDeclaration *vgate;
      if ((vgate = decl->isSharedStaticDtorDeclaration()->vgate))
	mi->sharedctorgates.safe_push (vgate);
      mi->shareddtors.safe_push (decl);
    }
  else if (decl->isStaticDtorDeclaration())
    {
      VarDeclaration *vgate;
      if ((vgate = decl->isStaticDtorDeclaration()->vgate))
	mi->ctorgates.safe_push (vgate);
      mi->dtors.safe_push (decl);
    }
  else if (decl->isUnitTestDeclaration())
    mi->unitTests.safe_push (decl);

  return new_irs;
}
