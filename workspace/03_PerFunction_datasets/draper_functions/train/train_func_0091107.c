recalcWidth(void)
{
	if(isHidden())
	{
		if(m_iWidth != 0)
		{
			m_iWidth = 0;
			return true;
		}

		return false;
	}
	else
		return _recalcWidth();
}
