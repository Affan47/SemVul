OnUserEventSelected(wxListEvent& event)
{
	for (unsigned int i = 0; i < CUserEvents::GetCount(); ++i) {
		IDC_PREFS_EVENTS_PAGE->Hide(i+1);
	}

	IDC_PREFS_EVENTS_PAGE->Show((event.GetData() - USEREVENTS_FIRST_ID) / USEREVENTS_IDS_PER_EVENT + 1, true);

	IDC_PREFS_EVENTS_PAGE->Layout();

	event.Skip();
}
