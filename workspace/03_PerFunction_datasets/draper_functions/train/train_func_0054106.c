add_long_closebrace_comment(void)
{
   chunk_t *pc;
   chunk_t *tmp;
   chunk_t *br_open;
   chunk_t *br_close;
   chunk_t *fcn_pc = NULL;
   chunk_t *sw_pc  = NULL;
   int     nl_count;

   pc = chunk_get_head();
   while ((pc = chunk_get_next_ncnl(pc)) != NULL)
   {
      if ((pc->type == CT_FUNC_DEF) ||
          (pc->type == CT_OC_MSG_DECL))
      {
         fcn_pc = pc;
      }
      else if (pc->type == CT_SWITCH)
      {

         sw_pc = pc;
      }
      if ((pc->type != CT_BRACE_OPEN) || ((pc->flags & PCF_IN_PREPROC) != 0))
      {
         continue;
      }

      br_open  = pc;
      nl_count = 0;

      tmp = pc;
      while ((tmp = chunk_get_next(tmp)) != NULL)
      {
         if (chunk_is_newline(tmp))
         {
            nl_count += tmp->nl_count;
         }
         else if ((tmp->level == br_open->level) &&
                  (tmp->type == CT_BRACE_CLOSE))
         {
            br_close = tmp;


            tmp = chunk_get_next(tmp);
            if ((tmp == NULL) || chunk_is_newline(tmp))
            {
               int     nl_min  = 0;
               chunk_t *tag_pc = NULL;

               if (br_open->parent_type == CT_SWITCH)
               {
                  nl_min = cpd.settings[UO_mod_add_long_switch_closebrace_comment].n;
                  tag_pc = sw_pc;
               }
               else if ((br_open->parent_type == CT_FUNC_DEF) ||
                        (br_open->parent_type == CT_OC_MSG_DECL))
               {
                  nl_min = cpd.settings[UO_mod_add_long_function_closebrace_comment].n;
                  tag_pc = fcn_pc;
               }

               if ((nl_min > 0) && (nl_count >= nl_min) && (tag_pc != NULL))
               {

                  c_token_t style = (cpd.lang_flags & (LANG_CPP | LANG_CS)) ?
                                    CT_COMMENT_CPP : CT_COMMENT;


                  insert_comment_after(br_close, style,
                                       tag_pc->len, tag_pc->str);
               }
            }
            break;
         }
      }
   }
}
