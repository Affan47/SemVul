AppendToAccessList (char *user)

{ char id[CF_MAXVARSIZE];
  struct passwd *pw;

Debug1("Adding to access list for %s\n",user);

if (isalpha((int)user[0]))
   {
   if ((pw = getpwnam(user)) == NULL)
      {
      yyerror("No such user in password database");
      return;
      }

   sprintf(id,"%d",pw->pw_uid);
   AppendItem(&VACCESSLIST,id,NULL);
   }
else
   {
   AppendItem(&VACCESSLIST,user,NULL);
   }
}
