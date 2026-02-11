handle_oc_message_send(chunk_t *os)
{
   chunk_t *tmp;
   chunk_t *cs = chunk_get_next(os);

   while ((cs != NULL) && (cs->level > os->level))
   {
      cs = chunk_get_next(cs);
   }

   if ((cs == NULL) || (cs->type != CT_SQUARE_CLOSE))
   {
      return;
   }

   LOG_FMT(LOCMSG, "%s: line %d, col %d\n", __func__, os->orig_line, os->orig_col);

   tmp = chunk_get_next_ncnl(cs);
   if (chunk_is_semicolon(tmp))
   {
      tmp->parent_type = CT_OC_MSG;
   }

   os->parent_type = CT_OC_MSG;
   os->flags      |= PCF_IN_OC_MSG;
   cs->parent_type = CT_OC_MSG;
   cs->flags      |= PCF_IN_OC_MSG;

   int     cnt   = 0;
   chunk_t *prev = NULL;

   for (tmp = chunk_get_next(os); tmp != cs; tmp = chunk_get_next(tmp))
   {
      tmp->flags |= PCF_IN_OC_MSG;
      if (tmp->type == CT_COLON)
      {
         tmp->type = CT_OC_COLON;
         if ((prev != NULL) && ((prev->type == CT_WORD) || (prev->type == CT_TYPE)))
         {

            chunk_t *pp = chunk_get_prev(prev);
            if ((pp != NULL) &&
                (pp->type != CT_OC_COLON) &&
                (pp->type != CT_ARITH))
            {
               prev->type       = CT_OC_MSG_NAME;
               tmp->parent_type = CT_OC_MSG_NAME;
            }
         }
      }
      if ((cnt <= 1) && ((tmp->type == CT_WORD) || (tmp->type == CT_TYPE)))
      {
         tmp->type = (cnt == 0) ? CT_OC_MSG_CLASS : CT_OC_MSG_FUNC;
      }
      prev = tmp;
      cnt++;
   }
}
