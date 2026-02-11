InstOrNewPolicyBroken(pkgCache::PkgIterator I)
{

   if (Cache[I].InstBroken() == true)
   {
      if (Debug == true)
	 std::clog << "  Dependencies are not satisfied for " << I << std::endl;
      return true;
   }


   if (Cache[I].NowPolicyBroken() == false &&
       Cache[I].InstPolicyBroken() == true)
   {
      if (Debug == true)
	 std::clog << "  Policy breaks with upgrade of " << I << std::endl;
      return true;
   }

   return false;
}
