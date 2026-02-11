EmitPostScrollEvent()
{
	wxCommandEvent evt(fzEVT_POSTSCROLL, wxID_ANY);
	AddPendingEvent(evt);
}
