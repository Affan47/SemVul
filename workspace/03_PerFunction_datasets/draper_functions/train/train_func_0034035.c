readXRef(Guint *pos, std::vector<Guint> *followedXRefStm) {
  Parser *parser;
  Object obj;
  GBool more;


  obj.initNull();
  parser = new Parser(NULL,
	     new Lexer(NULL,
	       str->makeSubStream(start + *pos, gFalse, 0, &obj)),
	     gTrue);
  parser->getObj(&obj);


  if (obj.isCmd("xref")) {
    obj.free();
    more = readXRefTable(parser, pos, followedXRefStm);


  } else if (obj.isInt()) {
    obj.free();
    if (!parser->getObj(&obj)->isInt()) {
      goto err1;
    }
    obj.free();
    if (!parser->getObj(&obj)->isCmd("obj")) {
      goto err1;
    }
    obj.free();
    if (!parser->getObj(&obj)->isStream()) {
      goto err1;
    }
    if (trailerDict.isNone()) {
      xRefStream = gTrue;
    }
    more = readXRefStream(obj.getStream(), pos);
    obj.free();

  } else {
    goto err1;
  }

  delete parser;
  return more;

 err1:
  obj.free();
  delete parser;
  ok = gFalse;
  return gFalse;
}
