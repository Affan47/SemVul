initialize(PDFDoc *docA, Dict* dict) {
  Object obj1;

  if (dict->lookup("InkList", &obj1)->isArray()) {
    parseInkList(obj1.getArray());
  } else {
    inkListLength = 0;
    inkList = NULL;
    error(errSyntaxError, -1, "Bad Annot Ink List");
    ok = gFalse;
  }
  obj1.free();
}
