addSInt(DIELoc &Die, Optional<dwarf::Form> Form,
                        int64_t Integer) {
  addSInt(Die, (dwarf::Attribute)0, Form, Integer);
}
