CheckSize( CQueryObject * queryobject, struct filebaseobject * fbo )
{
	bool res = true;


	if ( queryobject->pMessageSearch->m_bSizeLimit )
	{
		if ( queryobject->pMessageSearch->m_eSizeType == esstATMOST )
		{
			if ( fbo->m_nSize > queryobject->pMessageSearch->m_nSize )
			{
				res = false;
			}
		}
		else
		{
			if ( fbo->m_nSize < queryobject->pMessageSearch->m_nSize )
			{
				res = false;
			}
		}
	}

	return res;
}
