_restoreVersion(XAP_Frame * pFrame, UT_uint32 iVersion)
{
	UT_return_val_if_fail(pFrame, false);

	if(isDirty())
	{
		if(pFrame->showMessageBox(XAP_STRING_ID_MSG_HistoryConfirmSave,
								  XAP_Dialog_MessageBox::b_YN,
								  XAP_Dialog_MessageBox::a_YES, getFilename())
		   == XAP_Dialog_MessageBox::a_NO)
		{
			return false;
		}

		save();
	}


	UT_uint32 i = 0;

	const char * pPath = g_strdup(getFilename());
	UT_return_val_if_fail(pPath, false);

	char * pDot = (char *)strrchr(pPath,'.');
	if(pDot)
	{
		*pDot = 0;
		pDot++;
	}

	UT_String s1, s2;

	do
	{
		i++;

		UT_String_sprintf(s2, "_version_%d-%d", iVersion, i);

		s1 = pPath;
		s1 += s2;

		if(pDot && *pDot)
		{
			s1 += ".";
			s1 += pDot;
		}

	}
	while(UT_isRegularFile(s1.c_str()));

	FREEP(pPath);

	m_bDoNotAdjustHistory = true;
	saveAs(s1.c_str(), getLastSavedAsType());
	m_bDoNotAdjustHistory = false;


	_setMarkRevisions(false);
	m_bAutoRevisioning = false;

	UT_uint32 iRevisionId = findAutoRevisionId(iVersion);


	UT_return_val_if_fail( iRevisionId > 0, false );
	iRevisionId--;

	if(rejectAllHigherRevisions(iRevisionId))
	{


		UT_sint32 iCount = getHistoryCount();
		const AD_VersionData * pVLast = NULL;
		time_t iEditTime = 0;

		for(UT_sint32 j = 0; j < iCount; ++j)
		{
			AD_VersionData * v = (AD_VersionData *)m_vHistory.getNthItem(j);
			if(!v)
			{
				UT_ASSERT_HARMLESS(UT_SHOULD_NOT_HAPPEN);
				continue;
			}

			if(v->getId() == iVersion)
			{
				pVLast = v;
				continue;
			}

			if(v->getId() > iVersion)
			{

				iEditTime += (v->getTime() - v->getStartTime());

				delete v;
				m_vHistory.deleteNthItem(j);
				iCount--;
				j--;
			}
		}

		UT_return_val_if_fail(pVLast,false);


		setDocVersion(iVersion);
		setLastSavedTime(pVLast->getTime());
		setLastOpenedTime(time(NULL));

		UT_ASSERT(m_iEditTime >= iEditTime);
		m_iEditTime -= iEditTime;


		m_bDoNotAdjustHistory = true;
		save();
		_clearUndo();
		m_bDoNotAdjustHistory = false;
	}

	return true;
}
