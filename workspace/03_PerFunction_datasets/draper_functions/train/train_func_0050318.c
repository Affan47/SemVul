handleMOD(Instruction *mod)
{
   if (mod->dType != TYPE_U32 && mod->dType != TYPE_S32)
      return;
   bld.setPosition(mod, false);

   Value *q = bld.getSSA();
   Value *m = bld.getSSA();

   bld.mkOp2(OP_DIV, mod->dType, q, mod->getSrc(0), mod->getSrc(1));
   handleDIV(q->getInsn());

   bld.setPosition(mod, false);
   expandIntegerMUL(&bld, bld.mkOp2(OP_MUL, TYPE_U32, m, q, mod->getSrc(1)));

   mod->op = OP_SUB;
   mod->setSrc(1, m);
}
