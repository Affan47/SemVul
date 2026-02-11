OnRun ()
{

  m_locale.Init();
  m_locale.AddCatalog(wxT(PACKAGE));

  wxLog::DontCreateOnDemand();
  wxLogStderr * stderrLog = new wxLogStderr;
  wxLogStderr * stdoutLog = new wxLogStderr(stdout);
  delete wxLog::SetActiveTarget(stderrLog);
#if wxCHECK_VERSION(2, 9, 0)
  wxLog::SetTimestamp("");
#else
  wxLog::SetTimestamp(NULL);
#endif

  Ed2kHash hash;
  size_t i;
  for (i=0;i<(m_filesToHash.GetCount());++i)
    {
      if (wxFileExists(m_filesToHash[i]))
        {
          if (m_flagVerbose)
            {
              wxLogMessage(_("Processing file number %u: %s"),i+1,m_filesToHash[i].c_str());

              if (m_flagPartHashes)
                {
                  wxLogMessage(_("You have asked for part hashes (Only used for files > 9.5 MB)"));
                }
            }

          if (hash.SetED2KHashFromFile(m_filesToHash[i], NULL))
            {

				wxLog::SetActiveTarget(stdoutLog);
                wxLogMessage(wxT("%s"), hash.GetED2KLink(m_flagPartHashes).c_str());

				wxLog::SetActiveTarget(stderrLog);
            }
        }
      else
        {
            if (m_flagVerbose)
                {
                    wxLogMessage(_("%s ---> Non existant file !\n"),m_filesToHash[i].c_str());
                }
        }
    }
  return 0;
}
