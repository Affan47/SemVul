compute_hash (KeywordExt *keyword) const
{
  int sum = _hash_includes_len ? keyword->_allchars_length : 0;

  const unsigned int *p = keyword->_selchars;
  int i = keyword->_selchars_length;
  for (; i > 0; p++, i--)
    sum += _asso_values[*p];

  return keyword->_hash_value = sum;
}
