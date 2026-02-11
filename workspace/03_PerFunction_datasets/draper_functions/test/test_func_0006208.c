Key_Pressed(GdkEventKey * e)
{
	int move = 0;
	UT_uint32 ix = m_ix;
	UT_uint32 iy = m_iy;
	UT_DEBUGMSG(("Current Symbol %x \n",m_CurrentSymbol));
	switch (e->keyval)
	{
	case GDK_KEY_Up:
		if(iy > 0)
		{
			iy--;
		}
		else
		{
			Scroll_Event (0);
		}
		move = -32;
		break;
	case GDK_KEY_Down:
		if(iy < 6)
		{
			iy++;
		}
		else
		{
			Scroll_Event (1);
		}
		move = 32;
		break;
	case GDK_KEY_Left:
		if(ix > 0)
		{
			ix--;
		}
		else if(iy > 0)
		{
			iy--;
			ix = 31;
		}
		else
		{
			Scroll_Event (0);
			ix = 31;

		}
		move = -1;
		break;
	case GDK_KEY_Right:
		if(ix < 31)
		{
			ix++;
		}
		else if(iy < 6)
		{
			iy++;
			ix = 0;
		}
		else
		{
			Scroll_Event (1);
			ix = 0;

		}
		move = 1;
		break;
	case GDK_KEY_Return:
		g_signal_stop_emission (G_OBJECT(m_windowMain),
			g_signal_lookup ("key_press_event",
			G_OBJECT_TYPE (m_windowMain)), 0);
		event_Insert();
		return TRUE ;
		break;
	}
	UT_DEBUGMSG(("m_ix %d m_iy %d \n",m_ix,m_iy));
	if (move != 0)
	{
		XAP_Draw_Symbol * iDrawSymbol = _getCurrentSymbolMap();
		UT_return_val_if_fail(iDrawSymbol,FALSE);
		UT_UCSChar c = iDrawSymbol->calcSymbolFromCoords(ix, iy);
		if (c)
		{ m_PreviousSymbol = m_CurrentSymbol;
		  m_CurrentSymbol = c;
  		  UT_DEBUGMSG(("m_CurrentSymbol %x \n",m_CurrentSymbol));
		  m_ix = ix;
		  m_iy = iy;
		}
		iDrawSymbol->drawarea(m_CurrentSymbol, m_PreviousSymbol);

		g_signal_stop_emission (G_OBJECT(m_windowMain),
								g_signal_lookup ("key_press_event",
												 G_OBJECT_TYPE (m_windowMain)), 0);
	}

	return FALSE ;
}
