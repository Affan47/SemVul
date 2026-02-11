clickdl_load_requirement(String name, const Vector<ArchiveElement> *archive, ErrorHandler *errh)
{
    ClickProvision *p = find_provision(name, 1);
    if (!p || p->loaded)
	return;

    ContextErrorHandler cerrh(errh, "While loading package '" + name + "':");

#ifdef CLICK_TOOL
    String suffix = ".to", cxx_suffix = ".t.cc", target = "tool";
#else
    String suffix = ".uo", cxx_suffix = ".u.cc", target = "userlevel";
#endif
    String package;


    int ai;
    if ((ai = archive_index(archive, name + suffix)) >= 0) {
	if (!check_tmpdir(*archive, &cerrh))
	    return;
	package = *tmpdir + "/" + name + suffix;
	FILE *f = fopen(package.c_str(), "wb");
	if (!f) {
	    cerrh.error("cannot open '%s': %s", package.c_str(), strerror(errno));
	    package = String();
	} else {
	    const ArchiveElement &ae = archive->at(ai);
	    fwrite(ae.data.data(), 1, ae.data.length(), f);
	    fclose(f);
	}
    } else if ((ai = archive_index(archive, name + cxx_suffix)) >= 0)
	package = click_compile_archive_file(name, *archive, ai, target, "-q", &cerrh);
    else if ((ai = archive_index(archive, name + ".cc")) >= 0)
	package = click_compile_archive_file(name, *archive, ai, target, "-q", &cerrh);
    else {

	package = clickpath_find_file(name + suffix, "lib", CLICK_LIBDIR);
	if (!package)
	    package = clickpath_find_file(name + ".o", "lib", CLICK_LIBDIR);
	if (!package)
	    cerrh.error("can't find required package '%s%s'\nin CLICKPATH or '%s'", name.c_str(), suffix.c_str(), CLICK_LIBDIR);
    }

    p->loaded = true;
    if (package)
	clickdl_load_package(package, &cerrh);
}
