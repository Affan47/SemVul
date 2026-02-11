RemovePublicHub( CString name, CString , CString  )
{
	m_Mutex.Lock();

	bool err = false;
	DCConfigHubItem * hubitem;

	hubitem = 0;

	if ( pPublicHubList->Get(name.ToUpper(),&hubitem) == 0 )
	{
		pPublicHubList_HostIndex->Del(hubitem->m_sHost);
		pPublicHubList->Del(hubitem->m_sName.ToUpper());
		err = true;
	}

	m_Mutex.UnLock();

	return err;
}
