TTFParseMaxp(struct SFNTTable *tbl, struct TTFmaxpData *out)
{
  struct Stream s = constructStream(tbl->buf, tbl->bufSize);
  enum StreamResult sResult;
  sResult = seekRelative(&s, 4);
  CHK_RD2(sResult);
  RD2(BEReadU16, &s, &out->numGlyphs, sResult);
  RD2(BEReadU16, &s, &out->maxPoints, sResult);
  RD2(BEReadU16, &s, &out->maxContours, sResult);
  RD2(BEReadU16, &s, &out->maxComponentPoints, sResult);
  RD2(BEReadU16, &s, &out->maxComponentContours, sResult);
  RD2(BEReadU16, &s, &out->maxZones, sResult);
  RD2(BEReadU16, &s, &out->maxTwilightPoints, sResult);
  RD2(BEReadU16, &s, &out->maxStorage, sResult);
  RD2(BEReadU16, &s, &out->maxFunctionDefs, sResult);
  RD2(BEReadU16, &s, &out->maxInstructionDefs, sResult);
  RD2(BEReadU16, &s, &out->maxStackElements, sResult);
  RD2(BEReadU16, &s, &out->maxSizeOfInstructions, sResult);
  RD2(BEReadU16, &s, &out->maxComponentElements, sResult);
  RD2(BEReadU16, &s, &out->maxComponentDepth, sResult);
  return EOT_SUCCESS;
}
