setMode(FV_VisualDragMode iEditMode)
{
	m_iVisualDragMode = iEditMode;
	if(iEditMode == FV_VisualDrag_NOT_ACTIVE)
	{
	    m_iInitialOffX = 0;
	    m_iInitialOffY = 0;
	    m_iLastX = 0;
	    m_iLastY = 0;
	    m_xLastMouse = 0;
	    m_yLastMouse = 0;
	}
}
