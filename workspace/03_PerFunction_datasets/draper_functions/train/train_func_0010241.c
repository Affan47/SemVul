set_svar (string varname, string varval)
{
  cerr << "set_svar (" << varname << ", " << varval << ")\n";
  uint i1 = varname.find ('[');
  if (i1 == -1)
    return set_svar (varname, 0, varval);
  if (varname[varname.length() - 1] != ']')
    {
      gi->debug_print ("set_svar: Badly formatted name " + varname);
      return;
    }
  string arrayname = varname.substr (0, i1);
  string indextext = varname.substr (i1+1, varname.length() - i1 - 2);
  cerr << "set_svar(" << varname << ") --> set_svar (" << arrayname << ", " << indextext << ")\n";
  for (uint c3 = 0; c3 < indextext.size(); c3 ++)
    if (indextext[c3] < '0' || indextext[c3] > '9')
      {
	set_svar (arrayname, get_ivar (indextext), varval);
	return;
      }
  set_svar (arrayname, parse_int (indextext), varval);
  return;
}
