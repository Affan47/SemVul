DepConfigure(DepIterator D)
{

   if (D.Reverse() == true)
      return true;

   for (; D.end() == false; ++D)
      if (D->Type == pkgCache::Dep::Depends)
	 if (VisitProvides(D,false) == false)
	    return false;
   return true;
}
