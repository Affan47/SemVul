getHintsOffset()
{
  int hintsOffset;

  Object obj1, obj2;
  if (linDict.isDict() &&
      linDict.dictLookup("H", &obj1)->isArray() &&
      obj1.arrayGetLength()>=2 &&
      obj1.arrayGet(0, &obj2)->isInt() &&
      obj2.getInt() > 0) {
    hintsOffset = obj2.getInt();
  } else {
    error(errSyntaxWarning, -1, "Hints table offset in linearization table is invalid");
    hintsOffset = 0;
  }
  obj2.free();
  obj1.free();

  return hintsOffset;
}
