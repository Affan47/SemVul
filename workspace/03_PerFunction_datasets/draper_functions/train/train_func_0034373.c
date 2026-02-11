_checkWord (const UT_UCSChar * ucszWord, size_t len)
{
	UT_return_val_if_fail (m_dict, SpellChecker::LOOKUP_ERROR);
	UT_return_val_if_fail (ucszWord, SpellChecker::LOOKUP_ERROR);
	UT_return_val_if_fail (len, SpellChecker::LOOKUP_ERROR);

	UT_UTF8String utf8 (ucszWord, len);

	switch (enchant_dict_check (m_dict, utf8.utf8_str(), utf8.byteLength()))
	{
	case -1:
		return SpellChecker::LOOKUP_ERROR;
	case 0:
		return SpellChecker::LOOKUP_SUCCEEDED;
	default:
		return SpellChecker::LOOKUP_FAILED;
	}
}
