indicator(struct csa *csa, int name)
{
      int ret;

      csa->fldno = 0;
loop:
      xassert(csa->c == '\n');
      read_char(csa);
      if (csa->c == ' ' || csa->c == '\n')
      {
         ret = 0;
      }
      else if (csa->c == '*')
      {
         while (csa->c != '\n')
            read_char(csa);
         goto loop;
      }
      else
      {
         int len = 0;
         while (csa->c != ' ' && csa->c != '\n' && len < 12)
         {  csa->field[len++] = (char)csa->c;
            read_char(csa);
         }
         csa->field[len] = '\0';
         if (!(strcmp(csa->field, "NAME")    == 0 ||
               strcmp(csa->field, "ROWS")    == 0 ||
               strcmp(csa->field, "COLUMNS") == 0 ||
               strcmp(csa->field, "RHS")     == 0 ||
               strcmp(csa->field, "RANGES")  == 0 ||
               strcmp(csa->field, "BOUNDS")  == 0 ||
               strcmp(csa->field, "ENDATA")  == 0))
            error(csa, "invalid indicator record\n");
         if (!name)
         {  while (csa->c != '\n')
               read_char(csa);
         }
         ret = 1;
      }
      return ret;
}
