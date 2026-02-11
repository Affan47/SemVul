OnCmdLineParsed(wxCmdLineParser& cmdline)
{

  wxFileName filename;
  size_t i;

  m_flagVerbose = cmdline.Found(wxT("v"));
  m_flagPartHashes = cmdline.Found(wxT("p"));

  m_filesToHash.Clear();
  for (i = 0; i < cmdline.GetParamCount(); ++i)
    {
      filename.Assign(cmdline.GetParam(i));
      m_filesToHash.Add(filename.GetFullPath());
    }
  m_filesToHash.Shrink();

  return true;
}
