getNumPages()
{
  if (numPages == -1)
  {
    Object catDict, pagesDict, obj;

    xref->getCatalog(&catDict);
    if (!catDict.isDict()) {
      error(-1, "Catalog object is wrong type (%s)", catDict.getTypeName());
      catDict.free();
      return 0;
    }
    catDict.dictLookup("Pages", &pagesDict);
    catDict.free();


    if (!pagesDict.isDict()) {
      error(-1, "Top-level pages object is wrong type (%s)",
          pagesDict.getTypeName());
      pagesDict.free();
      return 0;
    }

    pagesDict.dictLookup("Count", &obj);

    if (!obj.isNum()) {
      error(-1, "Page count in top-level pages object is wrong type (%s)",
         obj.getTypeName());
      numPages = 0;
    } else {
      numPages = (int)obj.getNum();
    }

    obj.free();
    pagesDict.free();
  }

  return numPages;
}
