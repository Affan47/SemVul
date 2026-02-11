Configure(wxWindow *parent, plugin_ptr old_plugin)
{
	m_parent = parent;


	m_google = dynamic_cast<OpenSync::Config::Google*> (old_plugin.get());
	if( m_google ) {
		m_google = m_google->Clone();
	}
	else {
		m_google = new OpenSync::Config::Google;
	}
	m_container.reset( m_google );


	return false;
}
