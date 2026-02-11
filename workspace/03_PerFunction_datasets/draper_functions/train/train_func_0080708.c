FindPkg(const string &Name, string const &Arch) {
	if (MultiArchCache() == false && Arch != "none") {
		if (Arch == "native" || Arch == "all" || Arch == "any" ||
		    Arch == NativeArch())
			return SingleArchFindPkg(Name);
		else
			return PkgIterator(*this,0);
	}


	pkgCache::GrpIterator Grp = FindGrp(Name);
	if (Grp.end() == true)
		return PkgIterator(*this,0);

	return Grp.FindPkg(Arch);
}
