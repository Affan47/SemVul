emit_fp_sop(uint32_t conditional_mod,
                        const struct prog_instruction *fpi,
                        fs_reg dst, fs_reg src0, fs_reg src1,
                        fs_reg one)
{
   for (int i = 0; i < 4; i++) {
      if (fpi->DstReg.WriteMask & (1 << i)) {
         fs_inst *inst;

         emit(CMP(reg_null_d, regoffset(src0, i), regoffset(src1, i),
                  conditional_mod));

         inst = emit(BRW_OPCODE_SEL, regoffset(dst, i), one, fs_reg(0.0f));
         inst->predicate = BRW_PREDICATE_NORMAL;
      }
   }
}
