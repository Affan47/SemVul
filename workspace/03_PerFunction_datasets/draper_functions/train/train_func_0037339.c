lj_ffrecord_func(jit_State *J)
{
  RecordFFData rd;
  uint32_t m = recdef_lookup(J->fn);
  rd.data = m & 0xff;
  rd.nres = 1;
  rd.argv = J->L->base;
  J->base[J->maxslot] = 0;
  (recff_func[m >> 8])(J, &rd);
  if (rd.nres >= 0) {
    if (J->postproc == LJ_POST_NONE) J->postproc = LJ_POST_FFRETRY;
    lj_record_ret(J, 0, rd.nres);
  }
}
