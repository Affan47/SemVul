emitHeader(bool UseOffsets) {
  DwarfUnit::emitHeader(UseOffsets);
  Asm->OutStreamer->AddComment("Type Signature");
  Asm->OutStreamer->EmitIntValue(TypeSignature, sizeof(TypeSignature));
  Asm->OutStreamer->AddComment("Type DIE Offset");

  Asm->OutStreamer->EmitIntValue(Ty ? Ty->getOffset() : 0,
                                 sizeof(Ty->getOffset()));
}
