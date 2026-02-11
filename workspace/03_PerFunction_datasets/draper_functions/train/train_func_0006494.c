removeStream(Ref refToStream) {
  const int lastpage = doc->getNumPages();
  for (int pg = 1; pg <= lastpage; ++pg) {
    Page *page = doc->getPage(pg);
    if (!page) {
      error(errSyntaxError, -1, "Failed check for shared annotation stream at page {0:d}", pg);
      continue;
    }
    Annots *annots = page->getAnnots();
    for (int i = 0; i < annots->getNumAnnots(); ++i) {
      AnnotAppearance *annotAp = annots->getAnnot(i)->getAppearStreams();
      if (annotAp && annotAp != this && annotAp->referencesStream(refToStream)) {
        return;
      }
    }
  }


  xref->removeIndirectObject(refToStream);
}
