initialize(XRef *xrefA, Catalog *catalog, Dict* dict) {
  Object obj1;

  sound = Sound::parseSound(dict->lookup("Sound", &obj1));
  if (!sound) {
    error(-1, "Bad Annot Sound");
    ok = gFalse;
  }
  obj1.free();

  if (dict->lookup("Name", &obj1)->isName()) {
    name = new GooString(obj1.getName());
  } else {
    name = new GooString("Speaker");
  }
  obj1.free();
}
