align_oc_msg_colon(chunk_t *so)
{
   int        span = cpd.settings[UO_align_oc_msg_colon_span].n;
   chunk_t    *pc;
   chunk_t    *tmp;
   AlignStack cas;
   AlignStack nas;
   int        level;
   bool       did_line;
   int        lcnt;
   bool       has_colon;


   nas.Reset();
   nas.m_right_align = true;

   cas.Start(span);

   level = so->level;
   pc    = chunk_get_next_ncnl(so, CNAV_PREPROC);

   did_line  = false;
   has_colon = false;
   lcnt      = 0;

   while ((pc != NULL) && (pc->level > level))
   {
      if (pc->level > (level + 1))
      {

      }
      else if (chunk_is_newline(pc))
      {
         if (!has_colon)
         {
            ++lcnt;
         }
         did_line  = false;
         has_colon = !has_colon;
      }
      else if (!did_line && (lcnt - 1 < span) && (pc->type == CT_OC_COLON))
      {
         has_colon = true;
         cas.Add(pc);
         tmp = chunk_get_prev(pc);
         if ((tmp != NULL) &&
             ((tmp->type == CT_OC_MSG_FUNC) ||
              (tmp->type == CT_OC_MSG_NAME)))
         {
            nas.Add(tmp);
         }
         did_line = true;
      }
      pc = chunk_get_next(pc, CNAV_PREPROC);
   }
   nas.End();
   cas.End();
}
