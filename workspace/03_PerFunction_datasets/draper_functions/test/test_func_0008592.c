emit_unspill(fs_inst *inst, fs_reg dst, uint32_t spill_offset,
                         int count)
{
   for (int i = 0; i < count; i++) {

      bool gen7_read = brw->gen >= 7 && spill_offset < (1 << 12) * REG_SIZE;

      fs_inst *unspill_inst =
         new(mem_ctx) fs_inst(gen7_read ?
                              SHADER_OPCODE_GEN7_SCRATCH_READ :
                              SHADER_OPCODE_GEN4_SCRATCH_READ,
                              dst);
      unspill_inst->offset = spill_offset;
      unspill_inst->ir = inst->ir;
      unspill_inst->annotation = inst->annotation;

      if (!gen7_read) {
         unspill_inst->base_mrf = 14;
         unspill_inst->mlen = 1;
      }
      inst->insert_before(unspill_inst);

      dst.reg_offset++;
      spill_offset += dispatch_width * sizeof(float);
   }
}
