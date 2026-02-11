ShowScope(char *name)


{ struct Scope *ptr;

for (ptr = VSCOPE; ptr != NULL; ptr=ptr->next)
   {
   if (name && strcmp(ptr->scope,name) != 0)
      {
      continue;
      }

   printf("\nConstant variables in SCOPE %s:\n",ptr->scope);
   PrintHashes(stdout,ptr->hashtable,0);
   }
}
