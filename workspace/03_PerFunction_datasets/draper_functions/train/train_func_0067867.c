recff_bit_unary(jit_State *J, RecordFFData *rd)
{
  TRef tr = lj_opt_narrow_tobit(J, J->base[0]);
  J->base[0] = (rd->data == IR_TOBIT) ? tr : emitir(IRTI(rd->data), tr, 0);
}
