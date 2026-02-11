setupEmbeddedCIDTrueTypeFont(GfxFont *font, Ref *id,
					       GooString *psName,
					       GBool needVerticalMetrics) {
  char *fontBuf;
  int fontLen;
  FoFiTrueType *ffTT;
  int i;


  for (i = 0; i < fontFileIDLen; ++i) {
    if (fontFileIDs[i].num == id->num &&
	fontFileIDs[i].gen == id->gen) {
      psName->appendf("_{0:d}", nextTrueTypeNum++);
      break;
    }
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
  if ((ffTT = FoFiTrueType::make(fontBuf, fontLen))) {
    if (globalParams->getPSLevel() >= psLevel3) {

      ffTT->convertToCIDType2(psName->getCString(),
			      ((GfxCIDFont *)font)->getCIDToGID(),
			      ((GfxCIDFont *)font)->getCIDToGIDLen(),
			      needVerticalMetrics,
			      outputFunc, outputStream);
    } else {

      ffTT->convertToType0(psName->getCString(),
			   ((GfxCIDFont *)font)->getCIDToGID(),
			   ((GfxCIDFont *)font)->getCIDToGIDLen(),
			   needVerticalMetrics,
			   outputFunc, outputStream);
    }
    delete ffTT;
  }
  gfree(fontBuf);


  writePS("%%EndResource\n");
}
