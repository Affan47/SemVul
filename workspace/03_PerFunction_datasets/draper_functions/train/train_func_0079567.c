setY(UT_sint32 iY)
{
	if(iY == m_iY)
	{
		return;
	}
	clearScreen();
	m_iY = iY;
}
