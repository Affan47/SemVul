Activate ()
{
	if (!m_Active)
		UpdateTagsList ();
	if (m_PropertyPage && m_pObject)
		gtk_widget_set_sensitive (m_PropertyPage, m_Active && static_cast < gcp::Text * > (m_pObject)->GetGlobalTag () == gccv::Invalid);
}
