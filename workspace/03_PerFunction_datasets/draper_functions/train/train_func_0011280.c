getInstruction(MCInst &MI, uint64_t &Size,
                                                 ArrayRef<uint8_t> Bytes,
                                                 uint64_t Address,
                                                 raw_ostream &OS,
                                                 raw_ostream &CS) const {

  Size = 0;
  if (Bytes.size() < 2)
    return MCDisassembler::Fail;


  const uint8_t *Table;
  if (Bytes[0] < 0x40) {
    Size = 2;
    Table = DecoderTable16;
  } else if (Bytes[0] < 0xc0) {
    Size = 4;
    Table = DecoderTable32;
  } else {
    Size = 6;
    Table = DecoderTable48;
  }


  if (Bytes.size() < Size)
    return MCDisassembler::Fail;


  uint64_t Inst = 0;
  for (uint64_t I = 0; I < Size; ++I)
    Inst = (Inst << 8) | Bytes[I];

  return decodeInstruction(Table, MI, Inst, Address, this, STI);
}
