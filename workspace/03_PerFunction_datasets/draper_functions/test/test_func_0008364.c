AssociationExists(struct TopicAssociation *list,char *fwd,char *bwd)

{ struct TopicAssociation *ta;
  int yfwd = false,ybwd = false;
  enum cfreport level;
  char l[CF_BUFSIZE],r[CF_BUFSIZE];

level = cf_verbose;

if (fwd == NULL || (fwd && strlen(fwd) == 0))
   {
   CfOut(cf_error,"","NULL forward association name\n");
   return NULL;
   }

if (bwd == NULL || (bwd && strlen(bwd) == 0))
   {
   CfOut(cf_verbose,"","NULL backward association name\n");
   }

for (ta = list; ta != NULL; ta=ta->next)
   {
   if (fwd && (strcmp(fwd,ta->fwd_name) == 0))
      {
      CfOut(cf_verbose,"","Association '%s' exists already\n",fwd);
      yfwd = true;
      }
   else if (fwd && ta->fwd_name)
      {
      strncpy(l,ToLowerStr(fwd),CF_MAXVARSIZE);
      strncpy(r,ToLowerStr(ta->fwd_name),CF_MAXVARSIZE);

      if (strcmp(l,r) == 0)
         {
         CfOut(cf_error,""," ! Association \"%s\" exists with different capitalization \"%s\"\n",fwd,ta->fwd_name);
         yfwd = true;
         }
      else
         {
         yfwd = false;
         }
      }
   else
      {
      yfwd = false;
      }

   if (bwd && (strcmp(bwd,ta->bwd_name) == 0))
      {
      CfOut(cf_verbose,""," ! Association '%s' exists already\n",bwd);
      ybwd = true;
      }
   else if (bwd && ta->bwd_name)
      {
      strncpy(l,ToLowerStr(bwd),CF_MAXVARSIZE);
      strncpy(r,ToLowerStr(ta->bwd_name),CF_MAXVARSIZE);

      if (strcmp(l,r) == 0)
         {
         CfOut(cf_inform,""," ! Association \"%s\" exists with different capitalization \"%s\"\n",bwd,ta->bwd_name);
         }

      ybwd = true;
      }
   else
      {
      ybwd = false;
      }

   if (yfwd && ybwd)
      {
      return ta;
      }
   }

return NULL;
}
