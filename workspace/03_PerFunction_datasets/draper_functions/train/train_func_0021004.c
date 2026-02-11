TestFunctionIntegrity()

{ int i,j;
  struct FnCallArg *args;

printf("%d. Testing internal function templates and knowledge\n",++NR);

for (i = 0; CF_FNCALL_TYPES[i].name != NULL; i++)
   {
   args = CF_FNCALL_TYPES[i].args;

   for (j = 0; args[j].pattern != NULL; j++)
      {
      CfOut(cf_verbose,""," -> .. arg %d %s = %s\n",j,args[j].pattern,args[j].description);
      }

   CfOut(cf_verbose,""," -> function %s (%d=%d args)\n",CF_FNCALL_TYPES[i].name,CF_FNCALL_TYPES[i].numargs,j);

   if (j != CF_FNCALL_TYPES[i].numargs)
      {
      printf(" !! Broken internal function declaration for \"%s\", prototype does not match declared number of args",CF_FNCALL_TYPES[i].name);
      }
   }

}
