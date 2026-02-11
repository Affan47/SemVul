interp_dir()
   {
   struct token *t, *t1;
   struct macro *m;
   struct str_buf *sbuf;
   char *s;


   if (src_stack->ntoks > 0)
      return src_stack->toks[--src_stack->ntoks];

   for (;;) {
      t = next_tok();
      if (t == NULL)
          return NULL;

      switch (t->tok_id) {
         case PpIf:
         case PpIfdef:
         case PpIfndef:
            start_select(t);
            break;

         case PpElif:
         case PpElse:
         case PpEndif:
            end_select(t);
            break;

         case PpInclude:
            incl_file(t);
            break;

         case PpDefine:
         case PpBegdef:
            define(t);
            break;

         case PpEnddef:
            errt1(t, "invalid context for #enddef");

         case PpUndef:


            t1 = NULL;
            nxt_non_wh(&t1);
            if (t1->tok_id != Identifier)
               errt1(t1, "#undef requires an identifier argument");
            m_delete(t1);
            free_t(t1);
            t1 = next_tok();
            if (t1->tok_id != PpDirEnd)
               errt1(t1, "syntax error for #undef");
            free_t(t1);
            free_t(t);
            break;

         case PpLine:

            break;

         case PpError:


            sbuf = get_sbuf();
            t1 = NULL;
            nxt_non_wh(&t1);
            toks_to_str(sbuf, t1);
            errt1(t, str_install(sbuf));
            break;

         case PpPragma:
         case PpSkip:


            t1 = next_tok();
            while (t1->tok_id != PpDirEnd) {
               free_t(t1);
               t1 = next_tok();
               }
            free_t(t);
            free_t(t1);
            break;

         case PpKeep:


            sbuf = get_sbuf();
            AppChar(*sbuf, '#');
            for (s = t->image; *s != '\0'; ++s)
               AppChar(*sbuf, *s);
            toks_to_str(sbuf, next_tok());
            t->image = str_install(sbuf);
            rel_sbuf(sbuf);
            return t;

         case PpNull:
            free_t(t);
            free_t(next_tok());
            break;

         default:


            if (t->tok_id == Identifier && !(t->flag & NoExpand) &&
                 (m = m_lookup(t)) != NULL) {
               if (max_recurse < 0 || m->recurse < max_recurse) {
                  if (expand(t, m))
                     free_t(t);
                  else
                     return t;
                  }
               else {
                  t->flag |= NoExpand;
                  return t;
                  }
               }
            else
               return t;
         }
      }
   }
