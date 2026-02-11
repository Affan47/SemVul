cp_expr_sizeof(CPState *cp, CPValue *k, int wantsz)
{
  CTSize sz;
  CTInfo info;
  if (cp_opt(cp, '(')) {
    if (cp_istypedecl(cp))
      k->id = cp_decl_abstract(cp);
    else
      cp_expr_comma(cp, k);
    cp_check(cp, ')');
  } else {
    cp_expr_unary(cp, k);
  }
  info = lj_ctype_info(cp->cts, k->id, &sz);
  if (wantsz) {
    if (sz != CTSIZE_INVALID)
      k->u32 = sz;
    else if (k->id != CTID_A_CCHAR)
      cp_err(cp, LJ_ERR_FFI_INVSIZE);
  } else {
    k->u32 = 1u << ctype_align(info);
  }
  k->id = CTID_UINT32;
}
