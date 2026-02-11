FlushCharacters() {
  pending_empty_ = false;
  if (characters_ != NULL) {
    RegExpTree* atom = new RegExpAtom(characters_->ToConstVector());
    characters_ = NULL;
    text_.Add(atom);
    LAST(ADD_ATOM);
  }
}
