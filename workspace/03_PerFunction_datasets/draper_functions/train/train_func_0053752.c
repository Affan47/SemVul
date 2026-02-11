findEncoding() const
{
  for (int i = 0; i < count(); ++i) {
    if (!iSheets[i]->encoding().isEmpty())
      return iSheets[i]->encoding();
  }
  return String();
}
