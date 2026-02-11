DeEscapeQuotedString(const char *from,char *to)

{ char *cp;
const char *sp;
  char start = *from;
  int len = strlen(from);

if (len == 0)
   {
   return 0;
   }

 for (sp=from+1,cp=to; (sp-from) < len; sp++,cp++)
    {
    if ((*sp == start))
       {
       *(cp) = '\0';

       if (*(sp+1) != '\0')
          {
          return (2+(sp - from));
          }

       return 0;
       }

    if (*sp == '\n')
       {
       P.line_no++;
       }

    if (*sp == '\\')
       {
       switch (*(sp+1))
          {
          case '\n':
              P.line_no++;
              sp+=2;
              break;

          case ' ':
              break;

          case '\\':
          case '\"':
          case '\'': sp++;
              break;
          }
       }

    *cp = *sp;
    }

 yyerror("Runaway string");
 *(cp) = '\0';
 return 0;
}
