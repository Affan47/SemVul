appendRowToMatrix(uint32_t offset) {
  if (Sequence.Empty) {

    Sequence.Empty = false;
    Sequence.LowPC = Row.Address;
    Sequence.FirstRowIndex = RowNumber;
  }
  ++RowNumber;
  LineTable->appendRow(Row);
  if (Row.EndSequence) {

    Sequence.HighPC = Row.Address;
    Sequence.LastRowIndex = RowNumber;
    if (Sequence.isValid())
      LineTable->appendSequence(Sequence);
    Sequence.reset();
  }
  Row.postAppend();
}
