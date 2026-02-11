output_cmt_start(cmt_reflow& cmt, chunk_t *pc)
{
   cmt.pc          = pc;
   cmt.column      = pc->column;
   cmt.brace_col   = pc->column_indent;
   cmt.base_col    = pc->column_indent;
   cmt.word_count  = 0;
   cmt.kw_subst    = false;
   cmt.xtra_indent = 0;
   cmt.cont_text   = "";
   cmt.reflow      = false;

   if (cmt.brace_col == 0)
   {
      cmt.brace_col = 1 + (pc->brace_level * cpd.settings[UO_output_tab_size].n);
   }


   if ((pc->parent_type == CT_COMMENT_START) ||
       (pc->parent_type == CT_COMMENT_WHOLE))
   {
      if (!cpd.settings[UO_indent_col1_comment].b &&
          (pc->orig_col == 1) &&
          !(pc->flags & PCF_INSERTED))
      {
         cmt.column    = 1;
         cmt.base_col  = 1;
         cmt.brace_col = 1;
      }
   }
   else if (pc->parent_type == CT_COMMENT_END)
   {

      chunk_t *prev = chunk_get_prev(pc);
      if (prev != NULL)
      {
         int col_min = prev->column + prev->len + 1;
         if (cmt.column < col_min)
         {
            cmt.column = col_min;
         }
      }
   }


   if (cpd.settings[UO_indent_cmt_with_tabs].b &&
       ((pc->parent_type == CT_COMMENT_END) ||
        (pc->parent_type == CT_COMMENT_WHOLE)))
   {
      cmt.column = next_tab_column(cmt.column - 1);


      pc->column = cmt.column;
   }
   cmt.base_col = cmt.column;


   cmt_output_indent(cmt.brace_col, cmt.base_col, cmt.column);

   cmt.kw_subst = (pc->flags & PCF_INSERTED) != 0;
}
