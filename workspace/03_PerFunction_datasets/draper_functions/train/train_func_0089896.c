scan_keyword(struct dsa *dsa)
{     int len = 0;
      if (skip_spaces(dsa, 0)) return 1;
      dsa->token[0] = '\0';
      while (isalnum(dsa->c) || dsa->c == '_')
      {  if (len == 31)
         {  xprintf("%s:%d: keyword `%s...' too long\n", dsa->fname,
               dsa->seqn, dsa->token);
            return 1;
         }
         dsa->token[len++] = (char)dsa->c, dsa->token[len] = '\0';
         if (get_char(dsa)) return 1;
      }
      if (len == 0)
      {  xprintf("%s:%d: missing keyword\n", dsa->fname, dsa->seqn);
         return 1;
      }
      return 0;
}
