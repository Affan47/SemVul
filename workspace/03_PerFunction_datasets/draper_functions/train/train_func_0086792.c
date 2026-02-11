getOrCreateSourceID(StringRef FileName,
                                               StringRef DirName) {


  return Asm->OutStreamer->EmitDwarfFileDirective(
      0, DirName, FileName,
      Asm->OutStreamer->hasRawTextSupport() ? 0 : getUniqueID());
}
