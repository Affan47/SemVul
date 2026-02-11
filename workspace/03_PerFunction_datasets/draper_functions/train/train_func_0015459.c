readSpecTable(std::istream &fin,
			      const std::string& stopcomment)
{
  std::string line;
  while (getline(fin, line)) {
    if (line.empty())
      continue;
    if (line[0] == '#') {
      if (line == stopcomment)
	break;
      continue;
    }
    Spec &spec = *new Spec;
    std::istringstream istr(line);
    istr >> spec;
    if (!istr)
      return false;
    m_IbanSpec.insert(specmap::value_type(spec.prefix,&spec));
  }
  return true;
}
