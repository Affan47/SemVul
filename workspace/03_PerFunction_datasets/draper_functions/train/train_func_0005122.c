HandleBroadcast(char *value)

{
if (strlen(CURRENTOBJECT) != 0)
   {
   yyerror("redefinition of broadcast address");
   printf("Previous val = %s\n",CURRENTOBJECT);
   }

if (strcmp("ones",value) == 0)
   {
   strcpy(CURRENTOBJECT,"one");
   return;
   }

if (strcmp("zeroes",value) == 0)
   {
   strcpy(CURRENTOBJECT,"zero");
   return;
   }

if (strcmp("zeros",value) == 0)
   {
   strcpy(CURRENTOBJECT,"zero");
   return;
   }

yyerror("Illegal broadcast specifier (ones/zeros)");
}
