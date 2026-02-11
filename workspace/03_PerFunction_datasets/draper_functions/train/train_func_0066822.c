quoting_options_from_style (enum quoting_style style)
{
  struct quoting_options o = { 0, 0, { 0 }, NULL, NULL };
  if (style == custom_quoting_style)
    abort ();
  o.style = style;
  return o;
}
