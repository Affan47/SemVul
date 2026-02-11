showIntroductionText(wxCommandEvent& aEvent)
{
  ::wxMessageBox(_("Welcome to DFArc, the Dink Smallwood front end!\n"
"\n"
"You can choose to play the original game (Dink Smallwood) or"
" Dink-Modules (D-Mods) which contain new adventures.\n"
"\n"
"After completing the main game, give some D-Mods a try.\n"
"There are hundreds of them, just click File-Download D-Mods."),
		 _("Introduction"),
		 wxOK | wxICON_INFORMATION, this);
  return;
}
