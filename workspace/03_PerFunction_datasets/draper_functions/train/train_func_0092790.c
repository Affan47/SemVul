ParseTypeTable() {
  if (Stream.EnterSubBlock(bitc::TYPE_BLOCK_ID_NEW))
    return Error("Malformed block record");

  return ParseTypeTableBody();
}
