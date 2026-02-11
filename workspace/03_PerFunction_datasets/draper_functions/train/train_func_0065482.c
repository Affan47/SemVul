handleADD(Instruction *add)
{
   Value *src0 = add->getSrc(0);
   Value *src1 = add->getSrc(1);

   if (src0->reg.file != FILE_GPR || src1->reg.file != FILE_GPR)
      return false;

   bool changed = false;
   if (!changed && prog->getTarget()->isOpSupported(OP_MAD, add->dType))
      changed = tryADDToMADOrSAD(add, OP_MAD);
   if (!changed && prog->getTarget()->isOpSupported(OP_SAD, add->dType))
      changed = tryADDToMADOrSAD(add, OP_SAD);
   return changed;
}
