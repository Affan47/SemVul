aspectCheckbox()
{
	if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON( m_wAspectCheck)) && (m_dHeightWidth > 0.0001))
		m_bAspect = true;
	else
		m_bAspect = false;
	setPreserveAspect( m_bAspect );
}
