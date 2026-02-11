sort_date(const void *s1, const void *s2)
{
   const FileInfo *p1=(*files_cmp)[*static_cast<const int*>(s1)];
   const FileInfo *p2=(*files_cmp)[*static_cast<const int*>(s2)];
   if(p1->date==p2->date)
      return sort_name(s1,s2);
   return p1->date>p2->date ? -rev_cmp : rev_cmp;
}
