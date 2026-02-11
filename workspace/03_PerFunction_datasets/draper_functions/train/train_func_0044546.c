lp_bld_tgsi_list_init(struct lp_build_tgsi_context * bld_base)
{
   bld_base->instructions = (struct tgsi_full_instruction *)
         MALLOC( LP_MAX_INSTRUCTIONS * sizeof(struct tgsi_full_instruction) );
   if (!bld_base->instructions) {
      return 0;
   }
   bld_base->max_instructions = LP_MAX_INSTRUCTIONS;
   return 1;
}
