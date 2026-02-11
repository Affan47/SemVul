dump(raw_ostream &OS) const {
  for (const auto &Decl : Decls)
    Decl.dump(OS);
}
