line_format() const
{
  if (content.get()) {
    Line *l = ::line_format(content.get());
    if (l) return l;
  }

  {
    string alt(get_attribute(attributes.get(), "ALT", ""));
    if (!alt.empty()) return new Line("[Java Applet: " + alt + ']');
  }

  {
    string code(get_attribute(attributes.get(), "CODE", ""));
    if (!code.empty()) return new Line("[Java Applet " + code + ']');
  }

  return new Line("[Java Applet]");
}
