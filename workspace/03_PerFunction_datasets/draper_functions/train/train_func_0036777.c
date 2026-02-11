recff_io_write(jit_State *J, RecordFFData *rd)
{
  TRef ud, fp = recff_io_fp(J, &ud, rd->data);
  TRef zero = lj_ir_kint(J, 0);
  TRef one = lj_ir_kint(J, 1);
  ptrdiff_t i = rd->data == 0 ? 1 : 0;
  for (; J->base[i]; i++) {
    TRef str = lj_ir_tostr(J, J->base[i]);
    TRef buf = emitir(IRT(IR_STRREF, IRT_P32), str, zero);
    TRef len = emitir(IRTI(IR_FLOAD), str, IRFL_STR_LEN);
    if (tref_isk(len) && IR(tref_ref(len))->i == 1) {
      TRef tr = emitir(IRT(IR_XLOAD, IRT_U8), buf, IRXLOAD_READONLY);
      tr = lj_ir_call(J, IRCALL_fputc, tr, fp);
      if (results_wanted(J) != 0)
	emitir(IRTGI(IR_NE), tr, lj_ir_kint(J, -1));
    } else {
      TRef tr = lj_ir_call(J, IRCALL_fwrite, buf, one, len, fp);
      if (results_wanted(J) != 0)
	emitir(IRTGI(IR_EQ), tr, len);
    }
  }
  J->base[0] = LJ_52 ? ud : TREF_TRUE;
}
