getAnnots(Catalog *catalog) {
  if (!annots) {
    Object obj;
    annots = new Annots(xref, catalog, getAnnots(&obj));
    obj.free();
  }

  return annots;
}
