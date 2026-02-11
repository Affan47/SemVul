initialize(PDFDoc *docA, Dict *dict) {
  Object obj1;

  if (!dict->lookupNF("Parent", &parent)->isRef()) {
    parent.initNull();
  }

  if (dict->lookup("Open", &obj1)->isBool()) {
    open = obj1.getBool();
  } else {
    open = gFalse;
  }
  obj1.free();
}
