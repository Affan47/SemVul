Str2Mode(char *s)

{ int a = CF_UNDEFINED;
  char output[CF_BUFSIZE];

if (s == NULL)
   {
   return 0;
   }

sscanf(s,"%o",&a);

if (a == CF_UNDEFINED)
   {
   snprintf(output,CF_BUFSIZE,"Error reading assumed octal value %s\n",s);
   ReportError(output);
   }

return (mode_t)a;
}
