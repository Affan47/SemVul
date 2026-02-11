tgsi_build_instruction(unsigned opcode,
                       unsigned saturate,
                       unsigned predicate,
                       unsigned num_dst_regs,
                       unsigned num_src_regs,
                       struct tgsi_header *header)
{
   struct tgsi_instruction instruction;

   assert (opcode <= TGSI_OPCODE_LAST);
   assert (saturate <= TGSI_SAT_MINUS_PLUS_ONE);
   assert (num_dst_regs <= 3);
   assert (num_src_regs <= 15);

   instruction = tgsi_default_instruction();
   instruction.Opcode = opcode;
   instruction.Saturate = saturate;
   instruction.Predicate = predicate;
   instruction.NumDstRegs = num_dst_regs;
   instruction.NumSrcRegs = num_src_regs;

   header_bodysize_grow( header );

   return instruction;
}
