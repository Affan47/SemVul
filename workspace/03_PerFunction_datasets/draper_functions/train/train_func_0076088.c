EmbedScript(ostream& ofs)
{
  ifstream ifs;
  if(!ifs || OpenDatafile(ifs, "svgformat.script").empty())
    return false;
  ofs << ifs.rdbuf();
  return true;
}
