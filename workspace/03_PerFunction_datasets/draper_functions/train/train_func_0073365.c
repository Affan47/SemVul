CheckBody(char *name,char *type)

{ struct Body *bp;
  char output[CF_BUFSIZE];

for (bp = BODIES; bp != NULL; bp=bp->next)
   {
   if ((strcmp(name,bp->name) == 0) && (strcmp(type,bp->type) == 0))
      {
      snprintf(output,CF_BUFSIZE,"Redefinition of body \"%s\" for \"%s\" is a broken promise",name,type);
      ReportError(output);
      ERRORCOUNT++;
      }
   }
}
