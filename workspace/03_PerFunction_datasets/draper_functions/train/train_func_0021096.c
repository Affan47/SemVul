count_to_loop_end(fs_inst *do_inst)
{
   int depth = 1;
   int ip = 1;
   for (fs_inst *inst = (fs_inst *)do_inst->next;
        depth > 0;
        inst = (fs_inst *)inst->next) {
      switch (inst->opcode) {
      case BRW_OPCODE_DO:
         depth++;
         break;
      case BRW_OPCODE_WHILE:
         depth--;
         break;
      default:
         break;
      }
      ip++;
   }
   return ip;
}
