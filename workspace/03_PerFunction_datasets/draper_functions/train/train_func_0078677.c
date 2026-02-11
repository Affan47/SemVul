writeTableToFile(OutStream* outStr, GBool writeAllEntries) {
  XRefTableWriter writer(outStr);
  outStr->printf("xref\r\n");
  writeXRef(&writer, writeAllEntries);
}
