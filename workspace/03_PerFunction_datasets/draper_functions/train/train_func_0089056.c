getCurrentPhonebook() throw(GsmException)
{
  if (_lastPhonebookName == "")
    {
      Parser p(_at->chat("^SPBS?", "^SPBS:"));

      _lastPhonebookName = p.parseString();
      p.parseComma();
      p.parseInt();
      p.parseComma();
      p.parseInt();
    }
  return _lastPhonebookName;
}
