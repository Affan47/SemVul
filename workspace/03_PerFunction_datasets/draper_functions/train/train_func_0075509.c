lj_ctype_info(CTState *cts, CTypeID id, CTSize *szp)
{
  CTInfo qual = 0;
  CType *ct = ctype_get(cts, id);
  for (;;) {
    CTInfo info = ct->info;
    if (ctype_isenum(info)) {

    } else if (ctype_isattrib(info)) {
      if (ctype_isxattrib(info, CTA_QUAL))
	qual |= ct->size;
      else if (ctype_isxattrib(info, CTA_ALIGN) && !(qual & CTFP_ALIGNED))
	qual |= CTFP_ALIGNED + CTALIGN(ct->size);
    } else {
      if (!(qual & CTFP_ALIGNED)) qual |= (info & CTF_ALIGN);
      qual |= (info & ~(CTF_ALIGN|CTMASK_CID));
      lua_assert(ctype_hassize(info) || ctype_isfunc(info));
      *szp = ctype_isfunc(info) ? CTSIZE_INVALID : ct->size;
      break;
    }
    ct = ctype_get(cts, ctype_cid(info));
  }
  return qual;
}
