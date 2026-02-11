align_backslash_newline(void)
{
   chunk_t *pc;

   pc = chunk_get_head();
   while (pc != NULL)
   {
      if (pc->type != CT_NL_CONT)
      {
         pc = chunk_get_next_type(pc, CT_NL_CONT, -1);
         continue;
      }
      pc = align_nl_cont(pc);
   }
}
