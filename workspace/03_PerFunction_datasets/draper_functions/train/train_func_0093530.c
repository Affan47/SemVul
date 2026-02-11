s_callback(GtkWidget * , gpointer user_data)
	{


		_wd * wd = static_cast<_wd *>(user_data);
		UT_return_if_fail(wd);
		GdkEvent * event = gtk_get_current_event();
		wd->m_pUnixToolbar->setCurrentEvent(event);
		if (!wd->m_blockSignal)
		{
			wd->m_pUnixToolbar->toolbarEvent(wd, 0, 0);
		}
	}
