getJS(int i)
{
  Object obj = jsNameTree.getValue(i);
  if (obj.isRef()) {
    Ref r = obj.getRef();
    obj.free();
    xref->fetch(r.num, r.gen, &obj);
  }

  if (!obj.isDict()) {
    obj.free();
    return 0;
  }
  Object obj2;
  if (!obj.dictLookup("S", &obj2)->isName()) {
    obj2.free();
    obj.free();
    return 0;
  }
  if (strcmp(obj2.getName(), "JavaScript")) {
    obj2.free();
    obj.free();
    return 0;
  }
  obj2.free();
  obj.dictLookup("JS", &obj2);
  GooString *js = 0;
  if (obj2.isString()) {
    js = new GooString(obj2.getString());
  }
  else if (obj2.isStream()) {
    Stream *stream = obj2.getStream();
    js = new GooString();
    stream->reset();
    int j;
    while ((j = stream->getChar()) != EOF) {
      js->append((char)j);
    }
  }
  obj2.free();
  obj.free();
  return js;
}
