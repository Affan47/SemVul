NeighbourItemMatches(struct Item *file_start,struct Item *location,char *string,enum cfeditorder pos,struct Attributes a,struct Promise *pp)

{ struct Item *ip;


for (ip = file_start; ip != NULL; ip = ip->next)
   {
   if (pos == cfe_before)
      {
      if (ip->next && ip->next == location)
         {
         if (MatchPolicy(string,ip->name,a,pp))
            {
            return true;
            }
         else
            {
            return false;
            }
         }
      }

   if (pos == cfe_after)
      {
      if (ip == location)
         {
         if (ip->next && MatchPolicy(string,ip->next->name,a,pp))
            {
            return true;
            }
         else
            {
            return false;
            }
         }
      }
   }

return false;
}
