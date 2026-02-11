Rlist2UidList(struct Rlist *uidnames,struct Promise *pp)

{ struct UidList *uidlist = NULL;
  struct Rlist *rp;
  char username[CF_MAXVARSIZE];
  uid_t uid;

for (rp = uidnames; rp != NULL; rp=rp->next)
   {
   username[0] = '\0';
   uid = Str2Uid(rp->item,username,pp);
   AddSimpleUidItem(&uidlist,uid,username);
   }

if (uidlist == NULL)
   {
   AddSimpleUidItem(&uidlist,CF_SAME_OWNER,NULL);
   }

return (uidlist);
}
