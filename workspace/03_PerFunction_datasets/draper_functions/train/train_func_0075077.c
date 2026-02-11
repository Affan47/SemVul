AuthorizeRoles(struct cfd_connection *conn,char *args)

{ char *sp;
  struct Auth *ap;
  char userid1[CF_MAXVARSIZE],userid2[CF_MAXVARSIZE];
  struct Rlist *rp,*defines = NULL;
  int permitted = false;

snprintf(userid1,CF_MAXVARSIZE,"%s@%s",conn->username,conn->hostname);
snprintf(userid2,CF_MAXVARSIZE,"%s@%s",conn->username,conn->ipaddr);

CfOut(cf_verbose,"","Checking authorized roles in %s\n",args);

if (strncmp(args,"--define",strlen("--define")) == 0)
   {
   sp = args + strlen("--define");
   }
else
   {
   sp = args + strlen("-D");
   }

while (*sp == ' ')
   {
   sp++;
   }

defines = SplitRegexAsRList(sp,"[,:;]",99,false);


for (rp = defines; rp != NULL; rp = rp->next)
   {
   CfOut(cf_verbose,""," -> Verifying %s\n",rp->item);

   for (ap = ROLES; ap != NULL; ap=ap->next)
      {
      if (FullTextMatch(ap->path,rp->item))
         {

         if (IsMatchItemIn(ap->accesslist,MapAddress(conn->ipaddr)) ||
             IsRegexItemIn(ap->accesslist,conn->hostname) ||
             IsRegexItemIn(ap->accesslist,userid1) ||
             IsRegexItemIn(ap->accesslist,userid2) ||
             IsRegexItemIn(ap->accesslist,conn->username)
             )
            {
            CfOut(cf_verbose,"","Attempt to define role/class %s is permitted\n",rp->item);
            permitted = true;
            }
         else
            {
            CfOut(cf_verbose,"","Attempt to define role/class %s is denied\n",rp->item);
            DeleteRlist(defines);
            return false;
            }
         }
      }

   }

if (permitted)
   {
   CfOut(cf_verbose,"","Role activation allowed\n");
   }
else
   {
   CfOut(cf_verbose,"","Role activation disallowed - abort execution\n");
   }

DeleteRlist(defines);
return permitted;
}
