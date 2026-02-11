suggestExactWord(const UT_UCSChar *word32, size_t length, UT_GenericVector<UT_UCSChar*>* pVecsugg)
{
	const char* pUTF8;
	const UT_UCS4Char *pWord;
	UT_UTF8String stUTF8;
	UT_UCS4Char *suggest32;
	int nSize;

	stUTF8.appendUCS4(word32, length);

	pUTF8 = stUTF8.utf8_str();

	UT_GenericVector<UT_UCS4Char *>* vec = m_map.pick(pUTF8);
	if (!vec)
		return false;

	const UT_uint32 nItems = vec->getItemCount();

	if (!nItems)
		return false;

	for (UT_uint32 iItem = nItems; iItem; --iItem)
	{
		pWord = vec->getNthItem(iItem - 1);
		nSize = sizeof(UT_UCS4Char) * (UT_UCS4_strlen(pWord) + 1);
		suggest32 = static_cast<UT_UCS4Char*>(g_try_malloc(nSize));
		memcpy (suggest32, pWord, nSize);

		pVecsugg->insertItemAt(suggest32, 0);
	}

	return true;
}
