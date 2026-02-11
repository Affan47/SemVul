parseDocument()
{
  String tag = parseToTag();
  if (tag == "?xml") {
    XmlAttributes attr;
    if (!parseAttributes(attr))
      return ESyntaxError;
    tag = parseToTag();
  }
  if (tag != "ipe")
    return ESyntaxError;

  XmlAttributes attr;
  if (!parseAttributes(attr))
    return ESyntaxError;

  String str;

  iStream << "<?xml version=\"1.0\"?>\n";
  iStream << "<!DOCTYPE ipe SYSTEM \"ipe.dtd\">\n";
  iStream << "<ipe";
  if (attr.has("version", str)) {
    int  v = Lex(str).getInt();
    if (v >= 70000)
      return ENotIpe6;
  }

  iStream << " version=\"70000\"";
  iStream << " creator=\"ipe6upgrade\">\n";


  bool needMediaSheet = false;
  iUseCropBox = true;
  Vector paper;

  tag = parseToTag();
  if (tag == "info") {
    XmlAttributes att;
    if (!parseAttributes(att))
      return ESyntaxError;

    if (att.has("media", str)) {
      Lex lex(str);
      Vector mbmin;
      lex >> mbmin.x >> mbmin.y >> paper.x >> paper.y;
      needMediaSheet = true;
    }

    iUseCropBox = (att.has("bbox", str) && str == "yes");

    iStream << "<info";
    writeAttr(att, "title");
    writeAttr(att, "author");
    writeAttr(att, "subject");
    writeAttr(att, "keywords");
    writeAttr(att, "pagemode");
    writeAttr(att, "numberpages");
    writeAttr(att, "created");
    writeAttr(att, "modified");
    iStream << "/>\n";

    tag = parseToTag();
  }
  if (tag == "preamble") {
    XmlAttributes att;
    if (!parseAttributes(att))
      return false;
    if (!parsePCDATA("preamble", str))
      return false;
    iStream << "<preamble>";
    iStream.putXmlString(str);
    iStream << "</preamble>\n";

    tag = parseToTag();
  }

  iStream << standardSheet;

  if (needMediaSheet) {
    iStream << "<ipestyle>\n";
    iStream << "<layout paper=\"" << paper
	    << "\" origin=\"0 0\" frame=\"" << paper << "\"/>\n";
    iStream << "</ipestyle>\n";
  }

  while (tag == "ipestyle" || tag == "bitmap") {
    if (tag == "ipestyle") {
      if (!parseStyle())
	return ESyntaxError;
    } else {
      if (!parseBitmap())
	return ESyntaxError;
    }
    tag = parseToTag();
  }

  while (tag == "page") {
    if (!parsePage())
      return ESyntaxError;
    tag = parseToTag();
  }

  if (tag != "/ipe")
    return ESyntaxError;
  iStream << "</ipe>\n";
  return ESuccess;
}
