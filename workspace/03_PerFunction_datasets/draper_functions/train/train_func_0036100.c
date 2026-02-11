OnEngineComboChange(wxCommandEvent &event)
{

	plugin_ptr old_app = GetCurrentPlugin();


	wxString newEngine = m_engine_combo->GetValue();
	if( m_apiset.os22() && newEngine == wxString(m_apiset.os22()->GetVersion(), wxConvUTF8) ) {
		m_engine = m_apiset.os22();
	}
	else if( m_apiset.os40() && newEngine == wxString(m_apiset.os40()->GetVersion(), wxConvUTF8) ) {
		m_engine = m_apiset.os40();
	}


	UpdateAppSizer();


	if( old_app.get() && m_engine->GetConverter().IsPluginSupported(old_app->GetPluginName(*m_engine)) ) {

		SelectApplication(old_app->GetAppName());
	}
	else {

		SelectApplication("");
	}
}
