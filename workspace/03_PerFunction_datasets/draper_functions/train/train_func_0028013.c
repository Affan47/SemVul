doSoftMask(Object *str, GBool alpha,
		     GfxColorSpace *blendingColorSpace,
		     GBool isolated, GBool knockout,
		     Function *transferFunc, GfxColor *backdropColor) {
  Dict *dict, *resDict;
  double m[6], bbox[4];
  Object obj1, obj2;
  int i;


  if (formDepth > 20) {
    return;
  }


  dict = str->streamGetDict();


  dict->lookup("FormType", &obj1);
  if (!(obj1.isNull() || (obj1.isInt() && obj1.getInt() == 1))) {
    error(errSyntaxError, getPos(), "Unknown form type");
  }
  obj1.free();


  dict->lookup("BBox", &obj1);
  if (!obj1.isArray()) {
    obj1.free();
    error(errSyntaxError, getPos(), "Bad form bounding box");
    return;
  }
  for (i = 0; i < 4; ++i) {
    obj1.arrayGet(i, &obj2);
    if (likely(obj2.isNum())) bbox[i] = obj2.getNum();
    else {
      obj2.free();
      obj1.free();
      error(errSyntaxError, getPos(), "Bad form bounding box (non number)");
      return;
    }
    obj2.free();
  }
  obj1.free();


  dict->lookup("Matrix", &obj1);
  if (obj1.isArray()) {
    for (i = 0; i < 6; ++i) {
      obj1.arrayGet(i, &obj2);
      if (likely(obj2.isNum())) m[i] = obj2.getNum();
      else m[i] = 0;
      obj2.free();
    }
  } else {
    m[0] = 1; m[1] = 0;
    m[2] = 0; m[3] = 1;
    m[4] = 0; m[5] = 0;
  }
  obj1.free();


  dict->lookup("Resources", &obj1);
  resDict = obj1.isDict() ? obj1.getDict() : (Dict *)NULL;


  ++formDepth;
  drawForm(str, resDict, m, bbox, gTrue, gTrue,
	  blendingColorSpace, isolated, knockout,
	  alpha, transferFunc, backdropColor);
  --formDepth;

  if (blendingColorSpace) {
    delete blendingColorSpace;
  }
  obj1.free();
}
