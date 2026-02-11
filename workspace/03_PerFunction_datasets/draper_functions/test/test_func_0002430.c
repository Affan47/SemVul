align_add(ChunkStack& cs, chunk_t *pc, int& max_col, int min_pad, bool squeeze)
{
   chunk_t *prev;
   int     min_col;

   prev = chunk_get_prev(pc);
   if ((prev == NULL) || chunk_is_newline(prev))
   {
      min_col = squeeze ? 1 : pc->column;
      LOG_FMT(LALADD, "%s: pc->col=%d max_col=%d min_pad=%d min_col=%d\n",
              __func__, pc->column, max_col, min_pad, min_col);
   }
   else
   {
      if (prev->type == CT_COMMENT_MULTI)
      {
         min_col = prev->orig_col_end + min_pad;
      }
      else
      {
         min_col = prev->column + prev->len + min_pad;
      }
      if (!squeeze)
      {
         if (min_col < pc->column)
         {
            min_col = pc->column;
         }
      }
      LOG_FMT(LALADD, "%s: pc->col=%d max_col=%d min_pad=%d min_col=%d multi:%s prev->col=%d prev->len=%d %s\n",
              __func__, pc->column, max_col, min_pad, min_col, (prev->type == CT_COMMENT_MULTI) ? "Y" : "N",
              (prev->type == CT_COMMENT_MULTI) ? prev->orig_col_end : prev->column, prev->len, get_token_name(prev->type));
   }

   if (cs.Empty())
   {
      max_col = 0;
   }

   cs.Push(pc);
   if (min_col > max_col)
   {
      max_col = min_col;
   }
}
