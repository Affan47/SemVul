mkMovFromReg(Value *dst, int id)
{
   Instruction *insn = new_Instruction(func, OP_MOV, typeOfSize(dst->reg.size));

   insn->setDef(0, dst);
   insn->setSrc(0, new_LValue(func, FILE_GPR));
   insn->getSrc(0)->reg.data.id = id;

   insert(insn);
   return insn;
}
