AddCharacter(uc16 c) {
  pending_empty_ = false;
  if (characters_ == NULL) {
    characters_ = new(zone()) ZoneList<uc16>(4);
  }
  characters_->Add(c);
  LAST(ADD_CHAR);
}
