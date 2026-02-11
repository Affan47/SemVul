WriteRequest(pkgDepCache &Cache, FILE* output, bool const Upgrade,
			bool const DistUpgrade, bool const AutoRemove,
			OpProgress *Progress)
{
   if (Progress != NULL)
      Progress->SubProgress(Cache.Head().PackageCount, _("Send request to solver"));
   unsigned long p = 0;
   string del, inst;
   for (pkgCache::PkgIterator Pkg = Cache.PkgBegin(); Pkg.end() == false; ++Pkg, ++p)
   {
      if (Progress != NULL && p % 100 == 0)
         Progress->Progress(p);
      string* req;
      pkgDepCache::StateCache &P = Cache[Pkg];
      if (P.Delete() == true)
	 req = &del;
      else if (P.NewInstall() == true || P.Upgrade() == true || P.ReInstall() == true ||
	       (P.Mode == pkgDepCache::ModeKeep && (P.iFlags & pkgDepCache::Protected) == pkgDepCache::Protected))
	 req = &inst;
      else
	 continue;
      req->append(" ").append(Pkg.FullName());
   }
   fprintf(output, "Request: EDSP 0.4\n");
   if (del.empty() == false)
      fprintf(output, "Remove: %s\n", del.c_str()+1);
   if (inst.empty() == false)
      fprintf(output, "Install: %s\n", inst.c_str()+1);
   if (Upgrade == true)
      fprintf(output, "Upgrade: yes\n");
   if (DistUpgrade == true)
      fprintf(output, "Dist-Upgrade: yes\n");
   if (AutoRemove == true)
      fprintf(output, "Autoremove: yes\n");
   if (_config->FindB("APT::Solver::Strict-Pinning", true) == false)
      fprintf(output, "Strict-Pinning: no\n");
   string solverpref("APT::Solver::");
   solverpref.append(_config->Find("APT::Solver", "internal")).append("::Preferences");
   if (_config->Exists(solverpref) == true)
      fprintf(output, "Preferences: %s\n", _config->Find(solverpref,"").c_str());
   fprintf(output, "\n");

   return true;
}
