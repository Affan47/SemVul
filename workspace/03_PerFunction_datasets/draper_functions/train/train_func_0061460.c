NewDescription(pkgCache::DescIterator &Desc,
					    const string &Lang,
					    const MD5SumValue &md5sum,
					    map_ptrloc idxmd5str)
{

   map_ptrloc const Description = AllocateInMap(sizeof(pkgCache::Description));
   if (Description == 0)
      return 0;


   Desc = pkgCache::DescIterator(Cache,Cache.DescP + Description);
   Desc->ID = Cache.HeaderP->DescriptionCount++;
   map_ptrloc const idxlanguage_code = WriteUniqString(Lang);
   if (unlikely(idxlanguage_code == 0))
      return 0;
   Desc->language_code = idxlanguage_code;

   if (idxmd5str != 0)
      Desc->md5sum = idxmd5str;
   else
   {
      map_ptrloc const idxmd5sum = WriteStringInMap(md5sum.Value());
      if (unlikely(idxmd5sum == 0))
	 return 0;
      Desc->md5sum = idxmd5sum;
   }

   return Description;
}
