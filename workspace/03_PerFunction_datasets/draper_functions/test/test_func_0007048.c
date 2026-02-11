NewProvidesAllArch(pkgCache::VerIterator &Ver, string const &Package,
				string const &Version) {
   for (std::vector<string>::const_iterator a = Architectures.begin();
	a != Architectures.end(); ++a)
   {
      if (NewProvides(Ver, Package, *a, Version) == false)
	 return false;
   }
   return true;
}
