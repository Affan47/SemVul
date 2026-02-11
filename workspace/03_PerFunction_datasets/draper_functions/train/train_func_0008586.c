read(const std::string &section, const std::string &key, std::string &val) const
{
  string k(normalize_key_name(key));

  const_section_iter_t s = sections.find(section);
  if (s == sections.end())
    return -ENOENT;
  ConfLine exemplar(k, "", "", "", 0);
  ConfSection::const_line_iter_t l = s->second.lines.find(exemplar);
  if (l == s->second.lines.end())
    return -ENOENT;
  val = l->val;
  return 0;
}
