Chop(char *str)

{ int i;

if ((str == NULL) || (strlen(str) == 0))
   {
   return;
   }

if (strlen(str) > CF_BUFSIZE)
   {
   CfLog(cferror,"Chop was called on a string that seemed to have no terminator","");
   return;
   }

for (i = strlen(str)-1; isspace((int)str[i]); i--)
   {
   str[i] = '\0';
   }
}
