update(ArrayRef<char> Data) {
  for (char Byte : Data) {
    int TableIdx = (CRC ^ Byte) & 0xff;
    CRC = CRCTable[TableIdx] ^ (CRC >> 8);
  }
}
