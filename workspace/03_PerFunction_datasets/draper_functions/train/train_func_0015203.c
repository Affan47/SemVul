crec_ct2irt(CTState *cts, CType *ct)
{
  if (ctype_isenum(ct->info)) ct = ctype_child(cts, ct);
  if (LJ_LIKELY(ctype_isnum(ct->info))) {
    if ((ct->info & CTF_FP)) {
      if (ct->size == sizeof(double))
	return IRT_NUM;
      else if (ct->size == sizeof(float))
	return IRT_FLOAT;
    } else {
      uint32_t b = lj_fls(ct->size);
      if (b <= 3)
	return IRT_I8 + 2*b + ((ct->info & CTF_UNSIGNED) ? 1 : 0);
    }
  } else if (ctype_isptr(ct->info)) {
    return (LJ_64 && ct->size == 8) ? IRT_P64 : IRT_P32;
  } else if (ctype_iscomplex(ct->info)) {
    if (ct->size == 2*sizeof(double))
      return IRT_NUM;
    else if (ct->size == 2*sizeof(float))
      return IRT_FLOAT;
  }
  return IRT_CDATA;
}
