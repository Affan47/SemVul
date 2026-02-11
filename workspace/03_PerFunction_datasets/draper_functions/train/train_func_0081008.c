IsValid()
{
  size_t size = s_valList.size();
  if (size < s_minCnt || size > s_maxCnt)
    return false;

  AA_LONG_MAP::iterator it = s_longMap.begin();
  while (it != s_longMap.end()) {
    AppArgOption_t* pOpt = (*it).second;
    if (pOpt->mand && !(pOpt->found))
      return false;
    if (pOpt->type == AAT_MANDATORY_VALUE && pOpt->found && !(pOpt->hasVal))
      return false;
    it++;
  }

  return true;
}
