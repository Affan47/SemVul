lj_opt_narrow_mod(jit_State *J, TRef rb, TRef rc, TValue *vc)
{
  TRef tmp;
  if (tvisstr(vc) && !lj_strscan_num(strV(vc), vc))
    lj_trace_err(J, LJ_TRERR_BADTYPE);
  if ((LJ_DUALNUM || (J->flags & JIT_F_OPT_NARROW)) &&
      tref_isinteger(rb) && tref_isinteger(rc) &&
      (tvisint(vc) ? intV(vc) != 0 : !tviszero(vc))) {
    emitir(IRTGI(IR_NE), rc, lj_ir_kint(J, 0));
    return emitir(IRTI(IR_MOD), rb, rc);
  }

  rb = lj_ir_tonum(J, rb);
  rc = lj_ir_tonum(J, rc);
  tmp = emitir(IRTN(IR_DIV), rb, rc);
  tmp = emitir(IRTN(IR_FPMATH), tmp, IRFPM_FLOOR);
  tmp = emitir(IRTN(IR_MUL), tmp, rc);
  return emitir(IRTN(IR_SUB), rb, tmp);
}
