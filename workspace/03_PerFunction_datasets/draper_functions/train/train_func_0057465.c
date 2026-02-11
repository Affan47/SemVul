gettext_quote (char const *msgid, enum quoting_style s)
{
  char const *translation = _(msgid);
  if (translation == msgid && s == clocale_quoting_style)
    translation = "\"";
  return translation;
}
