xhtml_stylehead(FILE *outf, Outchoices *od) {
  fprintf(outf, "<?xml version=\"1.0\" encoding=\"%s\"?>\n",
	  od->lngstr[charset_]);
  if (strcaseeq(od->stylesheet, "none"))
    fputs("<?xml-stylesheet href=\"#internalStyle\" type=\"text/css\"?>\n",
	  outf);
  else {
    fputs("<?xml-stylesheet href=\"", outf);
    xhtmlputs(outf, od, od->stylesheet, IN_HREF);
    fputs("\" type=\"text/css\"?>\n", outf);
  }
  fputs("<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"\n", outf);
  fputs("\t\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n", outf);
  fputs("<html xmlns=\"http://www.w3.org/1999/xhtml\">\n", outf);
  fputs("<head>\n", outf);
  fprintf(outf, "<title>%s ", od->lngstr[webstatsfor_]);
  xhtmlputs(outf, od, od->hostname, FROM_CFG);
  fputs("</title>\n", outf);
  fprintf(outf, "<meta http-equiv=\"Content-Type\" "
	  "content=\"text/html; charset=%s\" />\n", od->lngstr[charset_]);
  if (od->norobots)
    fputs("<meta name=\"robots\" content=\"noindex,nofollow\" />\n", outf);
  fprintf(outf, "<meta name=\"generator\" content=\"analog %s\" />\n",
	  VERSION);
  if (!strcaseeq(od->stylesheet, "none")) {
    fputs("<link href=\"", outf);
    xhtmlputs(outf, od, od->stylesheet, IN_HREF);
    fputs("\" rel=\"stylesheet\" />\n", outf);
  }
  else {
    fprintf(outf, "<style type=\"text/css\" id=\"internalStyle\">\n");
    fprintf(outf, "h2 {\n\tbackground-color: #A0C0F0;\n\twidth: 98%%;\n\t"
	  "padding: 3px 6px;\n}\n");
    fprintf(outf, "table {\n\ttext-align: right;\n\tmargin-left: 30px;\n\t"
	    "background-color: #D0E0F0;\n\tborder-collapse: collapse;\n}\n");
    fprintf(outf, "th {\n\tborder-bottom: 1px solid #404050;\n\t"
	  "border-right: 1px dotted #606070;\n\tborder-top: none;\n\t"
	  "border-left: none;\n\tpadding: 0px 5px 1px 5px;\n\t"
	  "font-weight: bold;\n\tbackground-color: #A0C0F0;\n}\n");
    fprintf(outf, "td {\n\tpadding: 0px 5px 1px 5px;\n\t"
	  "border-right: 1px dotted #606070;\n\tborder-left: none;\n\t"
	  "border-bottom: none;\n\tborder-top:none;\n}\n");
    fprintf(outf,
	    "td.%sx {\n\tfont-family: monospace;\n\twhite-space: pre;\n}\n",
	    od->cssprefix);
    fprintf(outf, ".%sxl {\n\ttext-align: left;\n\tborder-right: none;\n}\n",
	    od->cssprefix);
    fprintf(outf, ".%sxr {\n\ttext-align: right;\n\tborder-right: none;\n}\n",
	    od->cssprefix);
    fprintf(outf, ".%sbar {\n\ttext-align: left;\n\tborder-right: none;\n}\n",
	    od->cssprefix);
    fprintf(outf,
	    "tr.%ssub {background-color: #C0C0FF;\n\tfont-style: italic;\n}\n",
	    od->cssprefix);
    fprintf(outf, ".%srepdesc {\n\tfont-style: italic;\n}\n", od->cssprefix);
    fprintf(outf, ".%srepspan {\n\tfont-style: italic;\n}\n", od->cssprefix);
    fprintf(outf, ".%sgoto {\n\tfont-size: small;\n}\n", od->cssprefix);
    fprintf(outf, ".%sgensumtitle {\n\tfont-weight: bold;\n}\n",
	    od->cssprefix);
    fprintf(outf, ".%sgototitle {\n\tfont-weight: bold;\n}\n", od->cssprefix);
    fprintf(outf, ".%sruntimetitle {\n\tfont-weight: bold;\n}\n",
	    od->cssprefix);
    fprintf(outf, "img {\n\tborder-style: none;\n}\n");
    fprintf(outf, "a:link {\n\tcolor: blue;\n\ttext-decoration: none;\n}\n");
    fprintf(outf,
	    "a:visited {\n\tcolor: purple;\n\ttext-decoration: none;\n}\n");
    fprintf(outf, "a:link:hover {\n\ttext-decoration: underline;\n}\n");
    fprintf(outf, "a:visited:hover {\n\ttext-decoration: underline;\n}\n");
    fprintf(outf, "a:link:active {\n\tcolor: red;\n\t"
	    "text-decoration: underline;\n}\n");
    fprintf(outf, "a:visited:active {\n\tcolor: red;\n\t"
	  "text-decoration: underline;\n}\n");
    fprintf(outf, "</style>\n");
  }
  fputs("</head>\n", outf);
  fputs("<body>\n", outf);
}
