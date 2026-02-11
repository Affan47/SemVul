OnLeftClick(wxMouseEvent &p_event)
{
  wxCommandEvent event(wxEVT_COMMAND_BUTTON_CLICKED);
  event.SetId(GetId());
  wxPostEvent(GetParent(), event);

  p_event.Skip();
}
