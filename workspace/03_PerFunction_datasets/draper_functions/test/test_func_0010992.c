scan_comment(struct dsa *dsa)
{     int len = 0;
      if (skip_spaces(dsa, 0)) return 1;
      dsa->token[0] = '\0';
      while (!(dsa->c == EOF || dsa->c == '\n'))
      {  if (len == 255)
         {  xprintf("%s:%d: comment too long\n", dsa->fname, dsa->seqn)
               ;
            return 1;
         }
         dsa->token[len++] = (char)dsa->c, dsa->token[len] = '\0';
         if (get_char(dsa)) return 1;
      }
      return 0;
}
