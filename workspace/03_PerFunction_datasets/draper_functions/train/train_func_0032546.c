GetProcColumnIndex(char *name1,char *name2,char **names)

{ int i;

for (i = 0; names[i] != NULL; i++)
   {
   if ((strcmp(names[i],name1) == 0) || (strcmp(names[i],name2) == 0))
      {
      return i;
      }
   }

CfOut(cf_verbose,""," INFO - process column %s/%s was not supported on this system",name1,name2);
return -1;
}
