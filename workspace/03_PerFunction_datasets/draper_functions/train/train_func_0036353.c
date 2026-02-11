parseDocument(Document &doc)
{
  Document::SProperties properties = doc.properties();

  String tag = parseToTag();
  if (tag == "?xml") {
    XmlAttributes attr;
    if (!parseAttributes(attr, true))
      return ESyntaxError;
    tag = parseToTag();
  }
  if (tag != "ipe")
    return ESyntaxError;

  XmlAttributes attr;
  if (!parseAttributes(attr))
    return ESyntaxError;

  Lex versLex(attr["version"]);
  int version;
  versLex >> version;
  if (version < OLDEST_FILE_FORMAT)
    return EVersionTooOld;
  if (version > IPELIB_VERSION)
    return EVersionTooRecent;

  attr.has("creator", properties.iCreator);

  tag = parseToTag();
  if (tag == "info") {
    XmlAttributes att;
    if (!parseAttributes(att))
      return ESyntaxError;

    properties.iTitle = att["title"];
    properties.iAuthor = att["author"];
    properties.iSubject = att["subject"];
    properties.iKeywords = att["keywords"];
    properties.iFullScreen = (att["pagemode"] == "fullscreen");
    properties.iNumberPages = (att["numberpages"] == "yes");
    properties.iCreated = att["created"];
    properties.iModified = att["modified"];

    tag = parseToTag();
  }
  if (tag == "preamble") {
    XmlAttributes att;
    if (!parseAttributes(att))
      return ESyntaxError;
    if (!parsePCDATA("preamble", properties.iPreamble))
      return ESyntaxError;

    tag = parseToTag();
  }


  Cascade *cascade = doc.cascade();

  while (tag == "ipestyle" || tag == "bitmap") {
    if (tag == "ipestyle") {
      StyleSheet *sheet = new StyleSheet();
      if (!parseStyle(*sheet)) {
	delete sheet;
	return ESyntaxError;
      }
      cascade->insert(0, sheet);
    } else {
      if (!parseBitmap())
	return ESyntaxError;
    }
    tag = parseToTag();
  }

  while (tag == "page") {

    Page *page = new Page;
    doc.push_back(page);
    if (!parsePage(*page))
      return ESyntaxError;
    tag = parseToTag();
  }

  doc.setProperties(properties);
  if (tag != "/ipe")
    return ESyntaxError;
  return ESuccess;
}
