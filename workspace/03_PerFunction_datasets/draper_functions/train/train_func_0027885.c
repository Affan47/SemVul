handleSUCLAMP(Instruction *insn)
{
   ImmediateValue imm;
   int32_t val = insn->getSrc(2)->asImm()->reg.data.s32;
   int s;
   Instruction *add;

   assert(insn->srcExists(0) && insn->src(0).getFile() == FILE_GPR);


   if (insn->getSrc(0)->refCount() > 1)
      return;
   add = insn->getSrc(0)->getInsn();
   if (!add || add->op != OP_ADD ||
       (add->dType != TYPE_U32 &&
        add->dType != TYPE_S32))
      return;


   for (s = 0; s < 2; ++s)
      if (add->src(s).getImmediate(imm))
         break;
   if (s >= 2)
      return;
   s = s ? 0 : 1;

   val += imm.reg.data.s32;
   if (val > 31 || val < -32)
      return;

   if (add->src(s).getFile() != FILE_GPR || add->src(s).mod != Modifier(0))
      return;

   bld.setPosition(insn, false);

   insn->setSrc(2, bld.mkImm(val));
   insn->setSrc(0, add->getSrc(s));
}
