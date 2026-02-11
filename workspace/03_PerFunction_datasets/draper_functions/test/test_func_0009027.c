cp_decl_align(CPState *cp, CPDecl *decl)
{
  CTSize al = 4;
  if (cp->tok == '(') {
    al = cp_decl_sizeattr(cp);
    al = al ? lj_fls(al) : 0;
  }
  CTF_INSERT(decl->attr, ALIGN, al);
  decl->attr |= CTFP_ALIGNED;
}
