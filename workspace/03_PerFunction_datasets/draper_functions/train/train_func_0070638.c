listUpdate(void)
{


	if(getSectionLayout() && (getSectionLayout()->getType()== FL_SECTION_HDRFTR))
	{
		m_pAutoNum = NULL;
		return;
	}
	if (m_pAutoNum == NULL)
		return;

	if (m_bStartList == true)
		m_pAutoNum->update(1);

	if ((m_bListLabelCreated == false) && (m_bStopList == false))
		_createListLabel();


	m_bForceSectionBreak = true;
	format();

}
