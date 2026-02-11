print(raw_ostream &OS, bool isSigned) const {
  SmallString<40> S;
  this->toString(S, 10, isSigned, false);
  OS << S;
}
