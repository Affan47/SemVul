zstoreSlot(asf)A asf;
{
  A alist=(A)(*asf->p),adata=(A)(asf->p[1]);
  I i;
  S svar,scx,vname,cvname;

  for(i=0;i<alist->n;++i)
  {
    svar=XS(alist->p[i]);
    vname=symsplit(svar,&scx);
    if(Opts.verbose) H("\343 PKG: %ld: Storing %s.%s\n", i,scx->n,vname->n);
    TempEgo.scx=iced((I)scx,(I)PK_SYM);
    TempEgo.vname=iced((I)vname,(I)PK_SYM);
    TempEgo.glob=icedAtom(adata->p[i]);
    cvname=symjoin(scx,vname);
    TempEgo.cvname=iced((I)cvname,(I)PK_SYM);
    AddEgoEntry(cvname,&TempEgo);
  }
  R 0;
}
