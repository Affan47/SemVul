newlines_cleanup_dup(void)
{
   chunk_t *pc;
   chunk_t *next;

   pc   = chunk_get_head();
   next = pc;

   while (pc != NULL)
   {
      next = chunk_get_next(next);
      if ((next != NULL) &&
          (pc->type == CT_NEWLINE) &&
          (next->type == CT_NEWLINE))
      {
         chunk_del(pc);
      }
      pc = next;
   }
}
