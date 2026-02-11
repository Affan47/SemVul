Type2Cfs(char *name)

{ int i;

for (i = 0; i < (int)cfs_nobtype; i++)
   {
   if (name && strcmp(CF_REMACCESS_SUBTYPES[i].subtype,name)==0)
      {
      break;
      }
   }

return (enum cfsbundle)i;
}
