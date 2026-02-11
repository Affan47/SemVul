CheckAccess(char *users)

{ char id[CF_MAXVARSIZE], *sp;
  struct passwd *pw;
  int uid,myuid;

myuid = getuid();

if (myuid == 0)
   {
   return;
   }

for (sp = users; *sp != '\0'; sp++)
   {
   id[0] = '\0';

   sscanf(sp,"%295[^,:]",id);

   sp += strlen(id);

   if (isalpha((int)id[0]))
      {
      if ((pw = getpwnam(id)) == NULL)
         {
         printf("cfrun: No such user (%s) in password database\n",id);
         continue;
         }

      if (pw->pw_uid == myuid)
         {
         return;
         }
      }
   else
      {
      uid = atoi(id);
      if (uid == myuid)
         {
         return;
         }
      }
   }

 printf("cfrun: you have not been granted permission to run cfrun\n");
 exit(0);
}
