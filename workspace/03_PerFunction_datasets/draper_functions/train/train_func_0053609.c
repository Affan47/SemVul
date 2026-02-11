_createPreviewFromGC(GR_Graphics* gc,
										   UT_uint32 width,
										   UT_uint32 height)
{
	UT_return_if_fail (gc);

	m_iWidth = width;
	m_iHeight = height;


	DELETEP(m_pListsPreview);

	m_pListsPreview = new AP_Lists_preview(gc, this);
	UT_return_if_fail (m_pListsPreview);

	m_pListsPreview->setWindowSize(width, height);


	generateFakeLabels();
	m_isListAtPoint = getBlock()->isListItem();
	if(m_isListAtPoint == false)
	{
		m_NewListType = NOT_A_LIST;
	}
}
