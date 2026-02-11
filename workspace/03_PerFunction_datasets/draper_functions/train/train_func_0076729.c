operator<< (ostream &o, const SVarRecord &sr)
{
  o << sr.name << ": ";
  if (sr.size () == 0)
    o << "(empty)";
  else if (sr.size() <= 1)
    o << "<" << sr.get(0) << ">";
  else
    for (uint i = 0; i < sr.size(); i ++)
      {
	o << i << ": <" << sr.get(i) << ">";
	if (i + 1 < sr.size())
	  o << ", ";
      }
  return o;
}
