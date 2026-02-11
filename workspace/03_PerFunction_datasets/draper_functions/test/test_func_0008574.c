isEndOfFileRecord() const
{
  return (this->groupCode == 0) && !strcmp(string, "EOF");
}
