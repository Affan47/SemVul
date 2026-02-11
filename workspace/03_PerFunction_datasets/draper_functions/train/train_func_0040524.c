addToCustomDict (const UT_UCSChar *word, size_t len)
{
	UT_return_val_if_fail (m_dict, false);

	if (word && len) {
		UT_UTF8String utf8 (word, len);
		enchant_dict_add_to_personal (m_dict, utf8.utf8_str(), utf8.byteLength());
		return true;
	}
	return false;
}
