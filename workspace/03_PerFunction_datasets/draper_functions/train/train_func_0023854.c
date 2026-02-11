emitGlobalConstantFP(const ConstantFP *CFP, AsmPrinter &AP) {
  APInt API = CFP->getValueAPF().bitcastToAPInt();


  if (AP.isVerbose()) {
    SmallString<8> StrVal;
    CFP->getValueAPF().toString(StrVal);

    if (CFP->getType())
      CFP->getType()->print(AP.OutStreamer->GetCommentOS());
    else
      AP.OutStreamer->GetCommentOS() << "Printing <null> Type";
    AP.OutStreamer->GetCommentOS() << ' ' << StrVal << '\n';
  }


  unsigned NumBytes = API.getBitWidth() / 8;
  unsigned TrailingBytes = NumBytes % sizeof(uint64_t);
  const uint64_t *p = API.getRawData();


  if (AP.getDataLayout().isBigEndian() && !CFP->getType()->isPPC_FP128Ty()) {
    int Chunk = API.getNumWords() - 1;

    if (TrailingBytes)
      AP.OutStreamer->EmitIntValue(p[Chunk--], TrailingBytes);

    for (; Chunk >= 0; --Chunk)
      AP.OutStreamer->EmitIntValue(p[Chunk], sizeof(uint64_t));
  } else {
    unsigned Chunk;
    for (Chunk = 0; Chunk < NumBytes / sizeof(uint64_t); ++Chunk)
      AP.OutStreamer->EmitIntValue(p[Chunk], sizeof(uint64_t));

    if (TrailingBytes)
      AP.OutStreamer->EmitIntValue(p[Chunk], TrailingBytes);
  }


  const DataLayout &DL = AP.getDataLayout();
  AP.OutStreamer->EmitZeros(DL.getTypeAllocSize(CFP->getType()) -
                            DL.getTypeStoreSize(CFP->getType()));
}
