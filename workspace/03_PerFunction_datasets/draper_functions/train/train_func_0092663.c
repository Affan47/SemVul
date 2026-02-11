sendChangeAuthorCR(pp_Author * pAuthor)
{
	const gchar * szAtts[3] = {PT_DOCPROP_ATTRIBUTE_NAME,"changeauthor",NULL};
	const gchar ** szProps = NULL;
	std::string storage;
	_buildAuthorProps(pAuthor, szProps, storage);
	UT_return_val_if_fail(szProps, false);
	bool b = createAndSendDocPropCR(szAtts,szProps);
	DELETEPV(szProps);
	return b;
}
