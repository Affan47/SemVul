isLexicalBlock() const {
  return DbgNode && getTag() == dwarf::DW_TAG_lexical_block;
}
