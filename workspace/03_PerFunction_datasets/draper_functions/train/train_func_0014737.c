saveIncrementalUpdate (OutStream* outStr)
{
  XRef *uxref;
  int c;

  str->reset();
  while ((c = str->getChar()) != EOF) {
    outStr->put(c);
  }
  str->close();

  uxref = new XRef();
  uxref->add(0, 65535, 0, gFalse);
  int objectsCount = 0;
  for(int i=0; i<xref->getNumObjects(); i++) {
    if ((xref->getEntry(i)->type == xrefEntryFree) &&
        (xref->getEntry(i)->gen == 0))
      continue;
    objectsCount++;
    if (xref->getEntry(i)->updated) {
      Object obj1;
      Ref ref;
      ref.num = i;
      ref.gen = xref->getEntry(i)->gen;
      xref->fetch(ref.num, ref.gen, &obj1);
      Guint offset = writeObject(&obj1, &ref, outStr);
      uxref->add(ref.num, ref.gen, offset, gTrue);
      obj1.free();
    }
  }
  if (uxref->getSize() == 0) {
    delete uxref;
    return;
  }

  Guint uxrefOffset = outStr->getPos();
  uxref->writeToFile(outStr, gFalse );

  writeTrailer(uxrefOffset, objectsCount, outStr, gTrue);

  delete uxref;
}
