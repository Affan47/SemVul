m_find(mname)
char *mname;
   {
   struct macro **mpp;

   for (mpp = &m_table[MHash(mname)]; *mpp != NULL && (*mpp)->mname != mname;
      mpp = &(*mpp)->next)
      ;
   return mpp;
   }
