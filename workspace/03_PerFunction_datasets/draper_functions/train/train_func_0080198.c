wxGetChoiceFromUser(wxWindow * parent, wxString const & message,
      wxString const & caption, wxArrayString const & choices,
      char * * clientData = 0, long style = wxCHOICEDLG_STYLE,
      wxPoint const & pos = wxDefaultPosition)
{
   wxSingleChoiceDialog d(parent, message, caption, choices, clientData, style, pos);
   d.ShowModal();
   return d.GetReturnCode() == wxID_CANCEL? -1 : d.GetSelection();
}
