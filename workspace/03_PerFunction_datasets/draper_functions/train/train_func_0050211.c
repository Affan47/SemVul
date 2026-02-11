line_format() const
{
  string type    = get_attribute(attributes.get(), "TYPE", "TEXT");
  string name    = get_attribute(attributes.get(), "NAME", "");
  string value   = get_attribute(attributes.get(), "VALUE", "");
  bool   checked = get_attribute(attributes.get(), "CHECKED", "0") != "0";
  int    size    = get_attribute(attributes.get(), "SIZE", -1);
  string src     = get_attribute(attributes.get(), "SRC", "");

  string res;
  if (cmp_nocase(type, "TEXT") == 0) {
    if (size == -1) size = 20;
    if (value.empty()) value = name;

    if ((int) value.length() < size) value.append(size - value.length(), ' ');
    res = '[' + value + ']';
  } else
  if (cmp_nocase(type, "PASSWORD") == 0) {
    if (size == -1) size = 20;
    res = '[' + string(size, '*') + ']';
  } else
  if (cmp_nocase(type, "CHECKBOX") == 0) {
    res = checked ? string("*") : (USE_UTF8 ? string("\u2070") : string(1, LATIN1_ordm));
  } else
  if (cmp_nocase(type, "RADIO") == 0) {
    res = checked ? '#' : 'o';
  } else
  if (cmp_nocase(type, "SUBMIT") == 0) {
    res = value.empty() ? string("[Submit]") : '[' + value + ']';
  } else
  if (cmp_nocase(type, "IMAGE") == 0) {
    res = "[Submit " + src + ']';
  } else
  if (cmp_nocase(type, "RESET") == 0) {
    res = value.empty() ? string("[Reset]") : '[' + value + ']';
  } else
  if (cmp_nocase(type, "FILE") == 0) {
    res = "[File]";
  } else
  if (cmp_nocase(type, "HIDDEN") == 0) {
    return 0;
  } else {
    res = "[Unknown INPUT type]";
  }

  return new Line(res);
}
