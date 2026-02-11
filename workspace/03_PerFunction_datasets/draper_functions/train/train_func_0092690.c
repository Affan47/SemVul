eliminate_dead_code(void)
{
   int i;

   for (i=0; i < this->next_temp; i++) {
      int last_read = get_last_temp_read(i);
      int j = 0;

      foreach_list_safe(node, &this->instructions) {
         glsl_to_tgsi_instruction *inst = (glsl_to_tgsi_instruction *) node;

         if (inst->dst.file == PROGRAM_TEMPORARY && inst->dst.index == i &&
             j > last_read)
         {
            inst->remove();
            delete inst;
         }

         j++;
      }
   }
}
