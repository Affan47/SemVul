VerifyPatterns(struct Promise *pp)

{ struct Item **start = &(pp->edcontext->file_start);
  struct Attributes a = {{0}};
  struct Item *begin_ptr,*end_ptr;
  struct CfLock thislock;
  char lockname[CF_BUFSIZE];


CfOut(cf_verbose,""," -> Looking at pattern %s\n",pp->promiser);


a = GetReplaceAttributes(pp);
a.transaction.ifelapsed = CF_EDIT_IFELAPSED;

if (!a.replace.replace_value)
   {
   cfPS(cf_error,CF_INTERPT,"",pp,a," !! The promised pattern replace (%s) had no replacement string",pp->promiser);
   return;
   }

if (!a.haveregion)
   {
   begin_ptr = *start;
   end_ptr = NULL;
   }
else if (!SelectRegion(*start,&begin_ptr,&end_ptr,a,pp))
   {
   cfPS(cf_error,CF_INTERPT,"",pp,a," !! The promised pattern replace (%s) could not select an edit region in %s",pp->promiser,pp->this_server);
   return;
   }

snprintf(lockname,CF_BUFSIZE-1,"replace-%s-%s",pp->promiser,pp->this_server);
thislock = AcquireLock(lockname,VUQNAME,CFSTARTTIME,a,pp,true);

if (thislock.lock == NULL)
   {
   return;
   }


if (ReplacePatterns(begin_ptr,end_ptr,a,pp))
   {
   (pp->edcontext->num_edits)++;
   }

DeleteScope("match");

YieldCurrentLock(thislock);
}
