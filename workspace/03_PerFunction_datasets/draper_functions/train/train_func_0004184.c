narrow_stripov_backprop(NarrowConv *nc, IRRef ref, int depth)
{
  jit_State *J = nc->J;
  IRIns *ir = IR(ref);
  if (ir->o == IR_ADDOV || ir->o == IR_SUBOV ||
      (ir->o == IR_MULOV && (nc->mode & IRCONV_CONVMASK) == IRCONV_ANY)) {
    BPropEntry *bp = narrow_bpc_get(nc->J, ref, IRCONV_TOBIT);
    if (bp) {
      ref = bp->val;
    } else if (++depth < NARROW_MAX_BACKPROP && nc->sp < nc->maxsp) {
      narrow_stripov_backprop(nc, ir->op1, depth);
      narrow_stripov_backprop(nc, ir->op2, depth);
      *nc->sp++ = NARROWINS(IRT(ir->o - IR_ADDOV + IR_ADD, IRT_INT), ref);
      return;
    }
  }
  *nc->sp++ = NARROWINS(NARROW_REF, ref);
}
