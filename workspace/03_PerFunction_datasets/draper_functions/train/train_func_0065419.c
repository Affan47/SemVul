lookup(string expr)
{
  map<string, RegComp*>::iterator iter = _re_map.find(expr);
  if (iter != _re_map.end())
  {
    return iter->second;
  }
  else
  {
    return NULL;
  }
}
