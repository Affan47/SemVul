align_func_proto(int span)
{
   chunk_t    *pc;
   bool       look_bro = false;
   AlignStack as;
   AlignStack as_br;

   LOG_FMT(LALIGN, "%s\n", __func__);
   as.Start(span, 0);
   as.m_gap = cpd.settings[UO_align_func_proto_gap].n;

   as_br.Start(span, 0);
   as_br.m_gap = cpd.settings[UO_align_single_line_brace_gap].n;

   for (pc = chunk_get_head(); pc != NULL; pc = chunk_get_next(pc))
   {
      if (chunk_is_newline(pc))
      {
         look_bro = false;
         as.NewLines(pc->nl_count);
         as_br.NewLines(pc->nl_count);
      }
      else if ((pc->type == CT_FUNC_PROTO) ||
               ((pc->type == CT_FUNC_DEF) &&
                cpd.settings[UO_align_single_line_func].b))
      {
         if ((pc->parent_type == CT_OPERATOR) &&
             cpd.settings[UO_align_on_operator].b)
         {
            as.Add(chunk_get_prev_ncnl(pc));
         }
         else
         {
            as.Add(pc);
         }
         look_bro = (pc->type == CT_FUNC_DEF) &&
                    cpd.settings[UO_align_single_line_brace].b;
      }
      else if (look_bro &&
               (pc->type == CT_BRACE_OPEN) &&
               (pc->flags & PCF_ONE_LINER))
      {
         as_br.Add(pc);
         look_bro = false;
      }
   }
   as.End();
   as_br.End();
}
