newlines_do_else(chunk_t *start, argval_t nl_opt)
{
   chunk_t *next;
   chunk_t *tmp;

   if ((nl_opt == AV_IGNORE) ||
       (((start->flags & PCF_IN_PREPROC) != 0) &&
        !cpd.settings[UO_nl_define_macro].b))
   {
      return;
   }

   next = chunk_get_next_ncnl(start);
   if ((next != NULL) &&
       ((next->type == CT_BRACE_OPEN) ||
        (next->type == CT_VBRACE_OPEN)))
   {
      if (!one_liner_nl_ok(next))
      {
         return;
      }
      if (next->type == CT_VBRACE_OPEN)
      {

         if (nl_opt & AV_ADD)
         {
            newline_iarf_pair(start, chunk_get_next_ncnl(next), nl_opt);
            tmp = chunk_get_next_type(next, CT_VBRACE_CLOSE, next->level);
            if (!chunk_is_newline(chunk_get_next_nc(tmp)) &&
                !chunk_is_newline(chunk_get_prev_nc(tmp)))
            {
               newline_add_after(tmp);
            }
         }
      }
      else
      {
         newline_iarf_pair(start, next, nl_opt);
         if ((nl_opt & AV_ADD) != 0)
         {
            tmp = chunk_get_next_nc(next);
            if ((tmp != NULL) && !chunk_is_newline(tmp))
            {
               newline_add_between(next, tmp);
            }
         }
      }
   }
}
