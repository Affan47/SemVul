uniqueTokens(set<string>& dst, const char* str)
{
  vector<string> buf;
  tokenize(buf, str, ",");
  for(vector<string>::iterator it = buf.begin(); it != buf.end(); ++it)
    dst.insert(*it);
}
