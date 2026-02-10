read_router_string(String text, const String &landmark, bool empty_ok,
		   ErrorHandler *errh)
{

    Vector<ArchiveElement> archive;
    if (text.length() && text[0] == '!') {
	ArchiveElement::parse(text, archive, errh);
	if (ArchiveElement *ae = ArchiveElement::find(archive, "config"))
	    text = ae->data;
	else {
	    errh->lerror(landmark, "archive has no %<config%> section");
	    text = String();
	}
    }


  if (!text.length() && !empty_ok)
    errh->lwarning(landmark, "empty configuration");
  LexerT lexer(errh, ignore_line_directives);
  lexer.reset(text, archive, landmark);


  while (lexer.ystatement())
    ;


  return lexer.finish(global_scope);
}
