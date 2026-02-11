process(const char *infile, bool file_is_expr, const char *outfile,
	ErrorHandler *errh)
{
    int before = errh->nerrors();

    String contents;
    if (file_is_expr)
	contents = infile;
    else {
	contents = file_string(infile, errh);
	if (!contents && errh->nerrors() != before)
	    return;
    }

    XML_Parser parser = XML_ParserCreateNS(0, '|');
    XML_SetElementHandler(parser, start_element_handler, end_element_handler);
    XML_UseParserAsHandlerArg(parser);
    xml_errh = errh;
    xml_file = filename_landmark(infile, file_is_expr);

    xstates.clear();
    xstates.push_back(CX_NONE);

    if (XML_Parse(parser, contents.data(), contents.length(), 1) == 0) {
	xml_error(parser, "XML parse error: %s", XML_ErrorString(XML_GetErrorCode(parser)));
	return;
    }

    if (xstack.size() == 0 && errh->nerrors() == before)
	errh->lerror(xml_file, "no configuration section");


    if (errh->nerrors() == before) {
	for (int i = 0; i < classes.size(); i++)
	    classes[i]->complete_elementclass(errh);
	xstack.back()->complete(errh);
	xstack.back()->router(errh)->check();
    }


    if (errh->nerrors() == before && ::flatten)
	xstack.back()->router(errh)->flatten(errh);


    if (errh->nerrors() == before)
	write_router_file(xstack.back()->router(errh), outfile, errh);


    for (int i = 0; i < classes.size(); i++)
	delete classes[i];
    classes.clear();
    if (xstack.size())
	delete xstack[0];
    xstack.clear();
    xstates.clear();
    class_id_map.clear();
}
