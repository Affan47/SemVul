setCountry(Letter2 code)
{
  ics_ << " country=" << quot;
  if (code)
    ics_ << char((code >> 8) & 0xff) << char(code & 0xff);
  else
    ics_ << falseString;
  ics_ << quot;
}
