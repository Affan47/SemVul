applyChanges()
{
	UT_DEBUGMSG(("Doing apply changes number props %d \n",m_vecProps.getItemCount()));
	if (m_vecProps.getItemCount() == 0)
		return;

    FV_View * pView = static_cast<FV_View *>(XAP_App::getApp()->getLastFocussedFrame()->getCurrentView());
	const gchar ** propsArray  = new const gchar * [m_vecProps.getItemCount()+1];
	propsArray[m_vecProps.getItemCount()] = NULL;

	UT_sint32 i = m_vecProps.getItemCount();
	UT_sint32 j;
	for(j= 0; j<i; j=j+2)
	{
		propsArray[j] = static_cast<gchar *>(m_vecProps.getNthItem(j));
		propsArray[j+1] = static_cast<gchar *>(m_vecProps.getNthItem(j+1));
	}

	pView->setCellFormat(propsArray, m_ApplyTo,m_pGraphic,m_sImagePath);
	delete [] propsArray;
	m_bSettingsChanged = false;
}
