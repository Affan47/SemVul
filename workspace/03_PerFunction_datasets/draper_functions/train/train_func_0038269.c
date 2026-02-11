get_closing_brace(chunk_t *start)
{
   chunk_t *pc;
   int     level = start->level;

   for (pc = start; (pc = chunk_get_next(pc)) != NULL; )
   {
      if (((pc->type == CT_BRACE_CLOSE) || (pc->type == CT_VBRACE_CLOSE)) && (pc->level == level))
      {
         return(pc);
      }

      if (!chunk_is_newline(pc) && (pc->level < level))
      {
         return(NULL);
      }
   }

   return(NULL);
}
