getVisDirection() const
{
#ifndef NO_BIDI_SUPPORT
 	FV_View * pView = _getView();
	if(pView && pView->getBidiOrder() != FV_Order_Visual)
	{
		if(pView->getBidiOrder() == FV_Order_Logical_LTR)
			return UT_BIDI_LTR;
		else
			return UT_BIDI_RTL;
	}
	else if(m_iVisDirection == static_cast<UT_BidiCharType>(UT_BIDI_UNSET))
	{
		if(m_pLine)
		{
			m_pLine->_createMapOfRuns();
			UT_ASSERT(m_iVisDirection !=  static_cast<UT_BidiCharType>(UT_BIDI_UNSET));
			return m_iVisDirection;
		}
		else if(getBlock())
			return getBlock()->getDominantDirection();
		else
		{
			bool b;
			XAP_App::getApp()->getPrefsValueBool(static_cast<const gchar*>(AP_PREF_KEY_DefaultDirectionRtl), &b);
			if(b)
				return UT_BIDI_RTL;
			else
				return UT_BIDI_LTR;
		}
	}
	else
		return m_iVisDirection;
#else
	return UT_BIDI_LTR;
#endif
}
