getInstruction(
    MCInst &Instr, uint64_t &Size, ArrayRef<uint8_t> Bytes, uint64_t Address,
    raw_ostream &VStream, raw_ostream &CStream) const {
  CommentStream = &CStream;

  InternalInstruction InternalInstr;

  dlog_t LoggerFn = logger;
  if (&VStream == &nulls())
    LoggerFn = nullptr;

  Region R(Bytes, Address);

  int Ret = decodeInstruction(&InternalInstr, regionReader, (const void *)&R,
                              LoggerFn, (void *)&VStream,
                              (const void *)MII.get(), Address, fMode);

  if (Ret) {
    Size = InternalInstr.readerCursor - Address;
    return Fail;
  } else {
    Size = InternalInstr.length;
    return (!translateInstruction(Instr, InternalInstr, this)) ? Success : Fail;
  }
}
