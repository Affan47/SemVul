outputMatcDefinitions(ostream& out, int nof_defs, char** defs, bool dsign)
{
  int i;


  for (i = 0; i < nof_defs; i++) {
    if ( 0 == strncmp("function", LibFront::trimLeft(defs[i]), 8) ) continue;
    if ( dsign ) out << '$';
    out << defs[i] << endl;
  }


  for (i = 0; i < nof_defs; i++) {
    if ( 0 != strncmp("function", LibFront::trimLeft(defs[i]), 8) ) continue;
    if ( dsign ) out << '$';
    out << defs[i] << endl;
  }

  return out;
}
