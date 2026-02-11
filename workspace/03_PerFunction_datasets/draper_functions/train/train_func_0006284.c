mod_case_brace(void)
{
   chunk_t *pc = chunk_get_head();
   chunk_t *next;

   while (pc != NULL)
   {
      next = chunk_get_next_ncnl(pc, CNAV_PREPROC);
      if (next == NULL)
      {
         return;
      }

      if ((cpd.settings[UO_mod_case_brace].a == AV_REMOVE) &&
          (pc->type == CT_BRACE_OPEN) &&
          (pc->parent_type == CT_CASE))
      {
         pc = mod_case_brace_remove(pc);
      }
      else if ((cpd.settings[UO_mod_case_brace].a & AV_ADD) &&
               (pc->type == CT_CASE_COLON) &&
               (next->type != CT_BRACE_OPEN) &&
               (next->type != CT_BRACE_CLOSE) &&
               (next->type != CT_CASE))
      {
         pc = mod_case_brace_add(pc);
      }
      else
      {
         pc = chunk_get_next_ncnl(pc, CNAV_PREPROC);
      }
   }
}
