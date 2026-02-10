CountChar(char *string,char sep)

{ char *sp;
  int count = 0;

if (string == NULL)
   {
   return 0;
   }

if (string && strlen(string) == 0)
   {
   return 0;
   }

for (sp = string; *sp != '\0'; sp++)
   {
   if (*sp == '\\' && *(sp+1) == sep)
      {
      ++sp;
      }
   else if (*sp == sep)
      {
      count++;
      }
   }

return count;
}
