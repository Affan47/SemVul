canNotFindTask(PackageContainerInterface * const , pkgCacheFile &, std::string pattern) {
	if (ShowError == true)
		_error->Insert(ErrorType, _("Couldn't find task '%s'"), pattern.c_str());
}
