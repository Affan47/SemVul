remove_trailing_eol(MMAPString * mmapstr)
{
  if (mmapstr->str[mmapstr->len - 1] == '\n') {
    mmapstr->len --;
    mmapstr->str[mmapstr->len] = '\0';
  }
  if (mmapstr->str[mmapstr->len - 1] == '\r') {
    mmapstr->len --;
    mmapstr->str[mmapstr->len] = '\0';
  }
}
