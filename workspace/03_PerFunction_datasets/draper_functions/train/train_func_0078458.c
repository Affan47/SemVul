_mesa_merge_mov_into_inst(struct prog_instruction *inst,
                          const struct prog_instruction *mov)
{


   const GLuint mask = get_src_arg_mask(mov, 0, NO_MASK);


   if (mask != (inst->DstReg.WriteMask & mask))
      return GL_FALSE;

   inst->SaturateMode |= mov->SaturateMode;


   switch (inst->Opcode) {


   case OPCODE_MOV:
   case OPCODE_MIN:
   case OPCODE_MAX:
   case OPCODE_ABS:
   case OPCODE_ADD:
   case OPCODE_MAD:
   case OPCODE_MUL:
   case OPCODE_SUB:
   {
      GLuint dst_to_src_comp[4] = {0,0,0,0};
      GLuint dst_comp, arg;
      for (dst_comp = 0; dst_comp < 4; ++dst_comp) {
         if (mov->DstReg.WriteMask & (1 << dst_comp)) {
            const GLuint src_comp = GET_SWZ(mov->SrcReg[0].Swizzle, dst_comp);
            ASSERT(src_comp < 4);
            dst_to_src_comp[dst_comp] = src_comp;
         }
      }


      for (arg = 0; arg < _mesa_num_inst_src_regs(inst->Opcode); arg++) {
         const GLuint arg_swz = inst->SrcReg[arg].Swizzle;
         inst->SrcReg[arg].Swizzle = 0;


         for (dst_comp = 0; dst_comp < 4; ++dst_comp) {
            GLuint src_comp, arg_comp;
            if ((mov->DstReg.WriteMask & (1 << dst_comp)) == 0)
               continue;
            src_comp = dst_to_src_comp[dst_comp];
            ASSERT(src_comp < 4);
            arg_comp = GET_SWZ(arg_swz, src_comp);
            ASSERT(arg_comp < 4);
            inst->SrcReg[arg].Swizzle |= arg_comp << (3*dst_comp);
         }
      }
      inst->DstReg = mov->DstReg;
      return GL_TRUE;
   }


   case OPCODE_RCP:
   case OPCODE_SIN:
   case OPCODE_COS:
   case OPCODE_RSQ:
   case OPCODE_POW:
   case OPCODE_EX2:
   case OPCODE_LOG:
   case OPCODE_DP2:
   case OPCODE_DP3:
   case OPCODE_DP4:
      inst->DstReg = mov->DstReg;
      return GL_TRUE;


   default:
      if (mov->SrcReg[0].Swizzle != SWIZZLE_XYZW ||
          inst->DstReg.WriteMask != WRITEMASK_XYZW)
         return GL_FALSE;
      inst->DstReg = mov->DstReg;
      return GL_TRUE;
   }
}
