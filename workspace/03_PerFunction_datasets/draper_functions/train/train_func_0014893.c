LoadFile(SuperAtomTable& table)
{

  ifstream ifs;
  if (OpenDatafile(ifs, "superatom.txt").length() == 0)
  {
    obErrorLog.ThrowError(__FUNCTION__, "Cannot open superatom.txt", obError);
    return false;
  }
  string ln;
  while(getline(ifs, ln))
  {
    if (ln[0]=='#' || ln.empty())
      continue;
    std::vector<string> vec;
    if(tokenize(vec, ln) && vec.size()>=3)
    {

      AliasItem item;
      item.right_form = vec[1];
      item.smiles     = vec[2];
      item.color      = vec.size()>=4 ? vec[3] : "";
      table[ vec[0] ] = item;
    }
  }
  return true;
}
