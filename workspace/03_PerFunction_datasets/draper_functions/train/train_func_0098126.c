canNotFindPkgName(pkgCacheFile &Cache,
			std::string const &str) {
	if (ShowError == true)
		_error->Insert(ErrorType, _("Unable to locate package %s"), str.c_str());
	return pkgCache::PkgIterator(Cache, 0);
}
