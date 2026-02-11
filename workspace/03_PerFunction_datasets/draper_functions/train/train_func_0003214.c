setupEmbeddedCIDType0Font(GfxFont *font, Ref *id,
					    GooString *psName) {
  char *fontBuf;
  int fontLen;
  FoFiType1C *ffT1C;
  int i;


  for (i = 0; i < fontFileIDLen; ++i) {
    if (fontFileIDs[i].num == id->num &&
	fontFileIDs[i].gen == id->gen)
      return;
  }


  if (fontFileIDLen >= fontFileIDSize) {
    fontFileIDSize += 64;
    fontFileIDs = (Ref *)greallocn(fontFileIDs, fontFileIDSize, sizeof(Ref));
  }
  fontFileIDs[fontFileIDLen++] = *id;


  writePSFmt("%%BeginResource: font {0:t}\n", psName);
  embFontList->append("%%+ font ");
  embFontList->append(psName->getCString());
  embFontList->append("\n");


  fontBuf = font->readEmbFontFile(xref, &fontLen);
  if ((ffT1C = FoFiType1C::make(fontBuf, fontLen))) {
    if (globalParams->getPSLevel() >= psLevel3) {

      ffT1C->convertToCIDType0(psName->getCString(), outputFunc, outputStream);
    } else {

      ffT1C->convertToType0(psName->getCString(), outputFunc, outputStream);
    }
    delete ffT1C;
  }
  gfree(fontBuf);


  writePS("%%EndResource\n");
}
