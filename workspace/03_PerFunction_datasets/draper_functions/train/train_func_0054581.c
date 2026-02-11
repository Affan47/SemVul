add(string expr, RegComp* regcomp)
{
  _re_map.insert(regex_pair(expr, regcomp));
}
