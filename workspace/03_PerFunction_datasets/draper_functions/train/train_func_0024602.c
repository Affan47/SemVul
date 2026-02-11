PreviewFile(CPartFile* file)
{
	wxString command;


	if (thePrefs::GetVideoPlayer().IsEmpty()) {
		wxMessageBox(_(
			"To prevent this warning to show up in every preview,\nset your preferred video player in preferences (default is mplayer)."),
			_("File preview"), wxOK, this);


		command = wxT("xterm -T \"aMule Preview\" -iconic -e xdg-open ") QUOTE wxT("$file") QUOTE;
	} else {
		command = thePrefs::GetVideoPlayer();
	}

	wxString partFile;
	wxString partName;


	if (!file->IsCompleted()) {

		partName = file->GetPartMetFileName().RemoveExt().GetRaw();
		partFile = thePrefs::GetTempDir().JoinPaths(file->GetPartMetFileName().RemoveExt()).GetRaw();
	} else {


		partName = file->GetFileName().GetRaw();
		partFile = file->GetFullName().GetRaw();
	}


	if (!command.Replace(wxT("$file"), wxT("%PARTFILE"))) {
		if ((command.Find(wxT("%PARTFILE")) == wxNOT_FOUND) && (command.Find(wxT("%PARTNAME")) == wxNOT_FOUND)) {


			command << wxT(" ") << QUOTE << wxT("%PARTFILE") << QUOTE;
		}
	}

#ifndef __WXMSW__


	partFile.Replace(QUOTE, wxT("\\") QUOTE);
	partName.Replace(QUOTE, wxT("\\") QUOTE);
#endif

	command.Replace(wxT("%PARTFILE"), partFile);
	command.Replace(wxT("%PARTNAME"), partName);


	CTerminationProcess *p = new CTerminationProcess(command);
	int ret = wxExecute(command, wxEXEC_ASYNC, p);
	bool ok = ret > 0;
	if (!ok) {
		delete p;
		AddLogLineC(CFormat( _("ERROR: Failed to execute external media-player! Command: `%s'") ) %
			command );
	}
}
