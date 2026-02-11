parse_source_file(ElementTypeInfo &etinfo,
			       bool do_header, String *includes)
{
  String fn = etinfo.header_file;
  if (!do_header && fn.substring(-3) == ".hh")
    fn = etinfo.header_file.substring(0, -3) + ".cc";


  if (_parsed_sources.get(fn) < 0) {
    String text;
    if (!etinfo.source_directory && _router->archive_index(fn) >= 0) {
      text = _router->archive(fn).data;
      if (do_header)
	etinfo.found_header_file = fn;
    } else if (String found = clickpath_find_file(fn, 0, etinfo.source_directory)) {
      text = file_string(found);
      if (do_header)
	etinfo.found_header_file = found;
    }
    _cxxinfo.parse_file(text, do_header, includes);
    _parsed_sources.set(fn, 1);
  }
}
