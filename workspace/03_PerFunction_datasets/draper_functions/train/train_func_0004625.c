charstring(const IndexIterator &iiter, int which) const
{
    const uint8_t *s1 = iiter[which];
    int slen = iiter[which + 1] - s1;
    String cs = _cff->data_string().substring(s1 - _cff->data(), slen);
    if (slen == 0)
	return 0;
    else if (_charstring_type == 1)
	return new Type1Charstring(cs);
    else
	return new Type2Charstring(cs);
}
