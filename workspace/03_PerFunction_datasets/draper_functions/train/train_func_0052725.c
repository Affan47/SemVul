OnStatusEvent(wxCommandEvent &event)
{
	m_load_status_text->SetLabel(event.GetString());
}
