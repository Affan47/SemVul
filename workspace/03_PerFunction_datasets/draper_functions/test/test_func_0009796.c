calculateValue(void)
{
	UT_UCSChar sz_ucs_FieldValue[FPFIELD_MAX_LENGTH + 1];
	sz_ucs_FieldValue[0] = 0;

	char szFieldValue[FPFIELD_MAX_LENGTH + 1];

	PD_Document * pDoc = getBlock()->getDocument();
	UT_return_val_if_fail(pDoc, false);


	const char * name = pDoc->getFilename();
	if (!name)
		name = "*";

	strncpy (szFieldValue, name, FPFIELD_MAX_LENGTH);
	szFieldValue[FPFIELD_MAX_LENGTH] = '\0';

	if (getField())
	  getField()->setValue(static_cast<const gchar*>(szFieldValue));

	UT_UCS4_strcpy_char(sz_ucs_FieldValue, szFieldValue);

	return _setValue(sz_ucs_FieldValue);
}
