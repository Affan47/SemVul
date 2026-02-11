cur_topslot(GCproto *pt, const BCIns *pc, uint32_t nres)
{
  BCIns ins = pc[-1];
  if (bc_op(ins) == BC_UCLO)
    ins = pc[bc_j(ins)];
  switch (bc_op(ins)) {
  case BC_CALLM: case BC_CALLMT: return bc_a(ins) + bc_c(ins) + nres-1+1;
  case BC_RETM: return bc_a(ins) + bc_d(ins) + nres-1;
  case BC_TSETM: return bc_a(ins) + nres-1;
  default: return pt->framesize;
  }
}
