Create(wxWindow* parent, wxWindowID id, wxEvtHandler* evtHandler)
{
   m_control = new wxChoice(parent,
                            id,
                            wxDefaultPosition,
                            wxDefaultSize,
                            mChoices);

   wxGridCellEditor::Create(parent, id, evtHandler);
   mHandler.ConnectEvent(m_control);
}
