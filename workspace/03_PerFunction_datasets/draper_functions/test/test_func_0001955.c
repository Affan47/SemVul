installed_type42(const String &ttf_filename, const String &ps_fontname, bool allow_generate, ErrorHandler *errh)
{
    (void) allow_generate, (void) ttf_filename, (void) errh;

    if (!ps_fontname)
	return String();

#if HAVE_KPATHSEA
# if HAVE_AUTO_TTFTOTYPE42
    if (!(force && allow_generate && ttf_filename && ttf_filename != "-" && getodir(O_TYPE42, errh))) {
# endif

	String file, path;
	if ((file = ps_fontname + ".t42", path = kpsei_string(kpsei_find_file(file.c_str(), KPSEI_FMT_TYPE42)))) {
	    if (path == "./" + file || path == file) {
		if (verbose)
		    errh->message("ignoring Type 42 file %s found with kpathsea in %<.%>", path.c_str());
	    } else {
		if (verbose)
		    errh->message("Type 42 file %s found with kpathsea at %s", file.c_str(), path.c_str());
		return path;
	    }
	}
# if HAVE_AUTO_TTFTOTYPE42
    }
# endif
#endif

#if HAVE_AUTO_TTFTOTYPE42

    if (allow_generate && ttf_filename && ttf_filename != "-" && getodir(O_TYPE42, errh)) {
	String t42_filename = odir[O_TYPE42] + "/" + ps_fontname + ".t42";
	if (t42_filename.find_left('\'') >= 0 || ttf_filename.find_left('\'') >= 0)
	    return String();
	String command = "ttftotype42 " + shell_quote(ttf_filename) + " " + shell_quote(t42_filename);
	int retval = mysystem(command.c_str(), errh);
	if (retval == 127)
	    errh->error("could not run %<%s%>", command.c_str());
	else if (retval < 0)
	    errh->error("could not run %<%s%>: %s", command.c_str(), strerror(errno));
	else if (retval != 0)
	    errh->error("%<%s%> failed", command.c_str());
	if (retval == 0) {
	    update_odir(O_TYPE42, t42_filename, errh);
	    return t42_filename;
	}
    }
#endif

    return String();
}
