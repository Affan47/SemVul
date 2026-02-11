releaseInstruction(Instruction *insn)
{


   insn->~Instruction();

   if (insn->asCmp())
      mem_CmpInstruction.release(insn);
   else
   if (insn->asTex())
      mem_TexInstruction.release(insn);
   else
   if (insn->asFlow())
      mem_FlowInstruction.release(insn);
   else
      mem_Instruction.release(insn);
}
