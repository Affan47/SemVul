set_of (pat, insn)
     rtx pat, insn;
{
  struct set_of_data data;
  data.found = NULL_RTX;
  data.pat = pat;
  note_stores (INSN_P (insn) ? PATTERN (insn) : insn, set_of_1, &data);
  return data.found;
}
