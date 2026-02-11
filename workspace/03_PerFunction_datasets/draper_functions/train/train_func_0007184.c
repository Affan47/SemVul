getLeftRulerInfo(AP_LeftRulerInfo * pInfo)
{


	if(getPoint()== 0)
	{
		m_iFreePass = AV_CHG_COLUMN | AV_CHG_FMTSECTION | AV_CHG_FMTBLOCK | AV_CHG_HDRFTR;
		return;
	}
	getLeftRulerInfo(getPoint(),pInfo);
}
