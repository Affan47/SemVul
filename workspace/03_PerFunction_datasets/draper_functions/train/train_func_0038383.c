parse() {
		cerr << "Parsing some html... ";
		tree<HTML::Node> tr;
		string html = "<head></head><body>\n\n\n\n<center>\n<table width=\"600\">\n<tbody><tr>\n<td width=\"120\"><a href=\"/index.html\"><img src=\"/adt-SUA/images/ADT_LOGO.gif\" alt=\"adt logo\" align=\"middle\" border=\"0\"></a></td>\n<td width=\"480\"><font size=\"+2\" face=\"helvetica,arial\"><b>Australian Digital Theses Program<br></b></font></td>\n</tr>\n</tbody></table>\n</center>\n<center>\n</center>\n</body>";

		HTML::ParserDom parser;
		parser.parse(html);
		tr = parser.getTree();
		cerr << tr << endl;
		cerr << " ok" << endl;
		return true;
	}
