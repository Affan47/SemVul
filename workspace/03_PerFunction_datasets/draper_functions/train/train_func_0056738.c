Write(ostream &strm) const {
  WriteType(strm, kSymbolTableMagicNumber);
  WriteType(strm, name_);
  WriteType(strm, available_key_);
  int64 size = symbols_.size();
  WriteType(strm, size);
  for (int64 i = 0; i < symbols_.size(); ++i) {
    int64 key = (i < dense_key_limit_) ? i : idx_key_[i - dense_key_limit_];
    WriteType(strm, symbols_.GetSymbol(i));
    WriteType(strm, key);
  }
  strm.flush();
  if (strm.fail()) {
    LOG(ERROR) << "SymbolTable::Write: write failed";
    return false;
  }
  return true;
}
