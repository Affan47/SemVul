getPrefixQuery(const TCHAR* _field, TCHAR* _termStr)
{
  if (!allowLeadingWildcard && _termStr[0] == _T('*')){
    _CLDELETE_LCARRAY(_termStr);
    _CLTHROWT(CL_ERR_Parse,_T("'*' not allowed as first character in PrefixQuery"));
  }
  if (lowercaseExpandedTerms) {
    _tcslwr(_termStr);
  }
  Term* t = _CLNEW Term(_field, _termStr);
  Query *q = _CLNEW PrefixQuery(t);
  _CLDECDELETE(t);
  return q;
}
