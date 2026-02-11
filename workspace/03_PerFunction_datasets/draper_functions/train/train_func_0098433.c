ListFromArgs(char *string)


{ struct Item *ip = NULL;
 int inquotes_level = 0,i = 0,argc=0;
  int inquote_level = 0;
  int paren_level = 0;
  char *sp,lastch = '\0';
  char item[CF_BUFSIZE];

memset(item,0,CF_BUFSIZE);

for (sp = string; *sp != '\0'; sp++)
   {
   switch (*sp)
      {
      case '\"':

          if (lastch == '\\')
             {
             if (inquotes_level == 0)
                {
                yyerror("Quoting error - escaped quote outside string");
                FatalError("Unrecoverable");
                }

             i--;
             }
          else
             {
             inquotes_level = 1 - inquotes_level;
             continue;
             }
          break;

      case '\'':

          if (lastch == '\\')
             {
             if (inquotes_level == 0)
                {
                yyerror("Quoting error - escaped quote outside string");
                FatalError("Unrecoverable");
                }

             i--;
             }
          else
             {
             inquote_level = 1 - inquote_level;
             continue;
             }
          break;

      case '(':

          if (inquotes_level == 0)
             {
             paren_level++;
             }
          break;

      case ')':

          if (inquotes_level == 0)
             {
             paren_level--;
             }
          break;

      case ',':

          if ((inquotes_level == 0) && (paren_level == 0))
             {
             item[i] = '\0';
             i = 0;
             AppendItem(&ip,item,"");
             Debug("ListArg[%d]=(%s)\n",argc++,item);
             memset(item,0,CF_BUFSIZE);
             continue;
             }
      }

   item[i++] = *sp;
   lastch = *sp;
   }

item[i] = '\0';
AppendItem(&ip,item,"");
Debug("ListArg[%d]=(%s)\n",argc,item);
return ip;
}
