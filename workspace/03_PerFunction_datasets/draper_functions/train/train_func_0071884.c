ReadNumber(byte** source) {


  byte* data = *source;
  if (data >= symbol_data_end_) return -1;
  byte input = *data;
  if (input == PreparseDataConstants::kNumberTerminator) {

    return -1;
  }
  int result = input & 0x7f;
  data++;
  while ((input & 0x80u) != 0) {
    if (data >= symbol_data_end_) return -1;
    input = *data;
    result = (result << 7) | (input & 0x7f);
    data++;
  }
  *source = data;
  return result;
}
