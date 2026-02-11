event_Replace(void)
{
	UT_UCS4String findEntryText;
	UT_UCS4String replaceEntryText;

	findEntryText = get_combobox_text(m_comboFind);
	replaceEntryText = get_combobox_text(m_comboReplace);

	setFindString(findEntryText.ucs4_str());
	setReplaceString(replaceEntryText.ucs4_str());

	if(!getReverseFind())
		findReplace();
	else
		findReplaceReverse();
}
