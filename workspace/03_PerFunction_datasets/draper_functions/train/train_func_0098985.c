lj_cconv_tv_bf(CTState *cts, CType *s, TValue *o, uint8_t *sp)
{
  CTInfo info = s->info;
  CTSize pos, bsz;
  uint32_t val;
  lua_assert(ctype_isbitfield(info));

  switch (ctype_bitcsz(info)) {
  case 4: val = *(uint32_t *)sp; break;
  case 2: val = *(uint16_t *)sp; break;
  case 1: val = *(uint8_t *)sp; break;
  default: lua_assert(0); val = 0; break;
  }

  pos = ctype_bitpos(info);
  bsz = ctype_bitbsz(info);
  lua_assert(pos < 8*ctype_bitcsz(info));
  lua_assert(bsz > 0 && bsz <= 8*ctype_bitcsz(info));
  if (pos + bsz > 8*ctype_bitcsz(info))
    lj_err_caller(cts->L, LJ_ERR_FFI_NYIPACKBIT);
  if (!(info & CTF_BOOL)) {
    CTSize shift = 32 - bsz;
    if (!(info & CTF_UNSIGNED)) {
      setintV(o, (int32_t)(val << (shift-pos)) >> shift);
    } else {
      val = (val << (shift-pos)) >> shift;
      if (!LJ_DUALNUM || (int32_t)val < 0)
	setnumV(o, (lua_Number)(uint32_t)val);
      else
	setintV(o, (int32_t)val);
    }
  } else {
    lua_assert(bsz == 1);
    setboolV(o, (val >> pos) & 1);
  }
  return 0;
}
