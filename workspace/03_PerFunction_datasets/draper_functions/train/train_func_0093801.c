ExtractInnerCf3VarString(const char *str,char *substr)

{ const char *sp;
  int bracks = 1;

Debug("ExtractInnerVarString( %s ) - syntax verify\n",str);

if (str == NULL || strlen(str) == 0)
   {
   return NULL;
   }

memset(substr,0,CF_BUFSIZE);

if (*(str+1) != '(' && *(str+1) != '{')
   {
   return NULL;
   }


for (sp = str+2; *sp != '\0' ; sp++)
   {
   switch (*sp)
      {
      case '(':
      case '{':
          bracks++;
          break;
      case ')':
      case '}':
          bracks--;
          break;

      default:
          if (isalnum((int)*sp) || strchr("_[]$.:-", *sp))
             {
             }
          else
             {
             Debug("Illegal character found: '%c'\n", *sp);
             Debug("Illegal character somewhere in variable \"%s\" or nested expansion",str);
             }
      }

   if (bracks == 0)
      {
      strncpy(substr,str+2,sp-str-2);
      Debug("Returning substring value %s\n",substr);
      return substr;
      }
   }

if (bracks != 0)
   {
   char output[CF_BUFSIZE];
   if (strlen(substr) > 0)
      {
      snprintf(output,CF_BUFSIZE,"Broken variable syntax or bracket mismatch - inner (%s/%s)",str,substr);
      yyerror(output);
      }
   return NULL;
   }

return sp-1;
}
