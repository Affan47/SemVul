parse_instruction_file(const char *filename, Signatures &sigs,
		       ErrorHandler *errh)
{
  String text = file_string(filename, errh);
  const char *s = text.data();
  int pos = 0;
  int len = text.length();
  while (pos < len) {
    int pos1 = pos;
    while (pos < len && s[pos] != '\n' && s[pos] != '\r')
      pos++;
    parse_instruction(text.substring(pos1, pos - pos1), sigs, errh);
    while (pos < len && (s[pos] == '\n' || s[pos] == '\r'))
      pos++;
  }
}
