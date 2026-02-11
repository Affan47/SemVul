VersionCheckSchedulePackage(struct Attributes a, struct Promise *pp, int matches, int installed)

{

enum package_actions policy = a.packages.package_policy;

switch(policy)
   {
   case cfa_deletepack:
      if (matches && installed)
         {
         return true;
         }
      break;

   case cfa_reinstall:
      if (matches && installed)
         {
         return true;
         }
      else
         {
	 cfPS(cf_verbose,CF_NOP,"",pp,a," -> Package (%s) already installed and matches criteria\n",pp->promiser);
	 }
      break;

   default:
      if (!installed || !matches)
         {
         return true;
	 }
      else
         {
	 cfPS(cf_verbose,CF_NOP,"",pp,a," -> Package (%s) already installed and matches criteria\n",pp->promiser);
	 }
      break;
   }

return false;
}
