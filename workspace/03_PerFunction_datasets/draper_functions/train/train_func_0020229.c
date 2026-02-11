reassoc_xref(jit_State *J, IRIns *ir)
{
  ptrdiff_t ofs = 0;
  if (ir->o == IR_ADD && irref_isk(ir->op2)) {
    IRIns *irk = IR(ir->op2);
    ofs = (LJ_64 && irk->o == IR_KINT64) ? (ptrdiff_t)ir_k64(irk)->u64 :
					   (ptrdiff_t)irk->i;
    ir = IR(ir->op1);
  }
  if (ir->o == IR_ADD) {

    IRIns *ir2, *ir1 = IR(ir->op1);
    int32_t shift = 0;
    IRRef idxref;

    if (ir1->o == IR_BSHL && irref_isk(ir1->op2))
      shift = IR(ir1->op2)->i;
    else if (ir1->o == IR_ADD && ir1->op1 == ir1->op2)
      shift = 1;
    else
      ir1 = ir;
    ir2 = IR(ir1->op1);

    if (ir2->o == IR_ADD && irt_isint(ir2->t) && irref_isk(ir2->op2))
      ofs += (ptrdiff_t)IR(ir2->op2)->i << shift;
    else
      return 0;
    idxref = ir2->op1;

    if (ir1 != ir &&
	!(idxref = reassoc_trycse(J, ir1->o, idxref,
				  ir1->o == IR_BSHL ? ir1->op2 : idxref)))
      return 0;
    if (!(idxref = reassoc_trycse(J, IR_ADD, idxref, ir->op2)))
      return 0;
    if (ofs != 0) {
      IRRef refk = tref_ref(lj_ir_kintp(J, ofs));
      if (!(idxref = reassoc_trycse(J, IR_ADD, idxref, refk)))
	return 0;
    }
    return idxref;
  }
  return 0;
}
