initialize(XRef *xrefA, Catalog *catalog, Dict *dict) {
  Object obj1;

  action = NULL;


  if (!dict->lookup("Dest", &obj1)->isNull()) {
    action = LinkAction::parseDest(&obj1);

  } else {
    obj1.free();
    if (dict->lookup("A", &obj1)->isDict()) {
      action = LinkAction::parseAction(&obj1, catalog->getBaseURI());
    }
  }
  obj1.free();

  if (dict->lookup("H", &obj1)->isName()) {
    const char *effect = obj1.getName();

    if (!strcmp(effect, "N")) {
      linkEffect = effectNone;
    } else if (!strcmp(effect, "I")) {
      linkEffect = effectInvert;
    } else if (!strcmp(effect, "O")) {
      linkEffect = effectOutline;
    } else if (!strcmp(effect, "P")) {
      linkEffect = effectPush;
    } else {
      linkEffect = effectInvert;
    }
  } else {
    linkEffect = effectInvert;
  }
  obj1.free();


  if (dict->lookup("QuadPoints", &obj1)->isArray()) {
    quadrilaterals = new AnnotQuadrilaterals(obj1.getArray(), rect);
  } else {
    quadrilaterals = NULL;
  }
  obj1.free();
}
