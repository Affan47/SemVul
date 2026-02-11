newline_add_between2(chunk_t *start, chunk_t *end,
                              const char *func, int line)
{
   chunk_t *pc;

   if ((start == NULL) || (end == NULL))
   {
      return(NULL);
   }

   LOG_FMT(LNEWLINE, "%s: '%.*s'[%s] line %d:%d and '%.*s' line %d:%d : caller=%s:%d\n",
           __func__, start->len, start->str, get_token_name(start->type),
           start->orig_line, start->orig_col,
           end->len, end->str, end->orig_line, end->orig_col, func, line);


   if (!one_liner_nl_ok(start))
   {
      return(NULL);
   }


   for (pc = start; pc != end; pc = chunk_get_next(pc))
   {
      if (chunk_is_newline(pc))
      {
         return(pc);
      }
   }


   if (end->type == CT_BRACE_OPEN)
   {
      pc = chunk_get_next(end);
      if (chunk_is_comment(pc))
      {
         pc = chunk_get_next(pc);
         if (chunk_is_newline(pc))
         {

            chunk_move_after(end, pc);
            return(pc);
         }
      }
   }

   return(newline_add_before(end));
}
