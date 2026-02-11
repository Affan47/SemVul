_ensureInsertionPointOnScreen()
{
	xxx_UT_DEBUGMSG(("FV_View::_ensureInsertionPointOnScreen called windowHeight %d Point %d \n",getWindowHeight(),getPoint()));


	if (getWindowHeight() <= 0)
		return false;


	if(getPoint() == 0)
		return false;

	xxx_UT_DEBUGMSG(("_ensure: [xp %ld][yp %ld][ph %ld] [w %ld][h %ld]\n",m_xPoint,m_yPoint,m_iPointHeight,getWindowWidth(),getWindowHeight()));

	bool bRet = false;
	if (m_yPoint < 0)
	{
		cmdScroll(AV_SCROLLCMD_LINEUP, (UT_uint32) (-(m_yPoint)));
		bRet = true;
	}
	else if ((static_cast<UT_uint32>(m_yPoint + m_iPointHeight)) >= (static_cast<UT_uint32>(getWindowHeight())))
	{
		cmdScroll(AV_SCROLLCMD_LINEDOWN, static_cast<UT_uint32>(m_yPoint + m_iPointHeight - getWindowHeight()));
		bRet = true;
	}


	if (m_xPoint < 0)
	{
		cmdScroll(AV_SCROLLCMD_LINELEFT, (UT_uint32) (-(m_xPoint) + getPageViewLeftMargin()/2));
		bRet = true;
	}
	else if ((static_cast<UT_uint32>(m_xPoint)) >= (static_cast<UT_uint32>(getWindowWidth())))
	{
		cmdScroll(AV_SCROLLCMD_LINERIGHT, static_cast<UT_uint32>(m_xPoint - getWindowWidth() + getPageViewLeftMargin()/2));
		bRet = true;
	}


	_fixInsertionPointCoords();

	return bRet;
}
