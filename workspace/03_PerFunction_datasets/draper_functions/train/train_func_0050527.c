dead_code_eliminate()
{
   bool progress = false;
   int pc = 0;

   calculate_live_intervals();

   foreach_list_safe(node, &this->instructions) {
      vec4_instruction *inst = (vec4_instruction *)node;

      if (inst->dst.file == GRF && !inst->has_side_effects()) {
         assert(this->virtual_grf_end[inst->dst.reg] >= pc);
         if (this->virtual_grf_end[inst->dst.reg] == pc) {


            switch (inst->opcode) {
            case BRW_OPCODE_ADDC:
            case BRW_OPCODE_SUBB:
            case BRW_OPCODE_MACH:
               inst->dst = dst_reg(retype(brw_null_reg(), inst->dst.type));
               break;
            default:
               inst->remove();
               break;
            }
            progress = true;
         }
      }

      pc++;
   }

   if (progress)
      invalidate_live_intervals();

   return progress;
}
