AddLiteral(CharClassBuilder* cc, Rune r, bool foldascii) {
  cc->AddRange(r, r);
  if (foldascii && 'a' <= r && r <= 'z')
    cc->AddRange(r + 'A' - 'a', r + 'A' - 'a');
}
