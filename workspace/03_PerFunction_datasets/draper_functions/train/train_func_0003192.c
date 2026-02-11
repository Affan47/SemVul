onInstall(wxCommandEvent &Event)
{
  int flags = wxPD_AUTO_HIDE | wxPD_APP_MODAL;
#if defined _WIN32 || defined __WIN32__ || defined __CYGWIN__


#else
  flags |= wxPD_REMAINING_TIME;
#endif
  wxProgressDialog* lInstallProgress = new wxProgressDialog(_("DFArc - Installing"), _T(""),
    100, this, flags);


  wxString destdir = mConfig->GetDinkrefDir();
  if (mDestdirBox->GetSelection() == 1)
    destdir = mConfig->mDModDir;

  int lError = mTar->Extract(destdir, lInstallProgress);
  lInstallProgress->Destroy();
  if (lError == 0)
    {
      if (mDmodName.Len() <= 0)
        {
	  mDmodName = _("The D-Mod you selected");
        }
      ::wxMessageBox(mDmodName + _(" was successfully installed."),
		   _("Success"), wxOK | wxICON_INFORMATION, this);

      wxString dmod_dir = mTar->getInstalledDmodDirectory();
      if (dmod_dir.Last() == _T('/'))
	dmod_dir = dmod_dir.RemoveLast();
      mConfig->mSelectedDmod = destdir + wxFileName::GetPathSeparator() + dmod_dir;
    }
  else
    {
      ::wxLogError(_("An error occured while extracting the .dmod file."));
    }
  ::wxRemoveFile(mTarFilePath);

  this->EndModal(wxID_OK);
}
