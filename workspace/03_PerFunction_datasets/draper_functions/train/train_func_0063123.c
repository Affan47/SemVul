event_BorderStyleChanged(void)
{
	if(m_wBorderStyle)
	{
		gint index = gtk_combo_box_get_active(GTK_COMBO_BOX(m_wBorderStyle));

		if (index >= 0 && index < BORDER_SHADING_NUMOFSTYLES)
		{
			UT_UTF8String style_utf8 = sBorderStyle[index];
			setBorderStyle(style_utf8);
			event_previewExposed();
		}
	}
}
