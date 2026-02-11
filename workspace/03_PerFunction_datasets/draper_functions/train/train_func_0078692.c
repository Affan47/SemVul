sortList(const GList<int> & list)
{
   GArray<int> a(list.size()-1);
   int cnt;
   GPosition pos;
   for(pos=list, cnt=0;pos;++pos, cnt++)
      a[cnt]=list[pos];

   qsort((int *) a, a.size(), sizeof(int), cmp);

   GList<int> l;
   for(int i=0;i<a.size();i++)
      l.append(a[i]);

   return l;
}
