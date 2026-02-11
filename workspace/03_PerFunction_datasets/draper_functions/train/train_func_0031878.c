Str2ServicePolicy(char *string)

{ static char *text[4] = { "start", "stop", "disable", NULL };
  int i;

for (i = 0; i < 3; i++)
   {
   if (string && (strcmp(text[i],string) == 0))
      {
      return i;
      }
   }

return cfsrv_nostatus;
}
