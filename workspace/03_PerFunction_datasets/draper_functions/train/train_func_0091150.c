begin_parse(const String &data, const String &filename,
		   LexerExtra *lextra, ErrorHandler *errh)
{
  _file = FileState(data, filename);
  _compact_config = false;

  _c = new Compound("", "", 0);
  _group_depth = 0;

  _lextra = lextra;
  _errh = (errh ? errh : ErrorHandler::default_handler());

  return lexical_scoping_in();
}
