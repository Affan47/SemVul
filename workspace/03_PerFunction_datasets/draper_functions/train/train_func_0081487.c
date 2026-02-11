Update(PkgIterator const &Pkg)
{

   RemoveStates(Pkg);
   UpdateVerState(Pkg);
   AddStates(Pkg);


   Update(Pkg.RevDependsList());


   if (Pkg->CurrentVer != 0)
      for (PrvIterator P = Pkg.CurrentVer().ProvidesList();
	   P.end() != true; ++P)
	 Update(P.ParentPkg().RevDependsList());


   if (PkgState[Pkg->ID].CandidateVer != 0)
      for (PrvIterator P = PkgState[Pkg->ID].CandidateVerIter(*this).ProvidesList();
	   P.end() != true; ++P)
	 Update(P.ParentPkg().RevDependsList());
}
