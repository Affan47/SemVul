add_source_file(const String& fn, ErrorHandler* errh)
{
    if (verbose && _source_files[fn] < 0)
	errh->message("adding source file '%s'", fn.c_str());
    _source_files.insert(fn, 1);
}
