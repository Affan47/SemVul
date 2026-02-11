SimpleGenSources(CommandLine &CmdL)
{
   if (CmdL.FileSize() < 2)
      return ShowHelp(CmdL);

   string Override;
   if (CmdL.FileSize() >= 3)
      Override = CmdL.FileList[2];

   string SOverride;
   if (Override.empty() == false)
      SOverride = Override + ".src";

   SOverride = _config->Find("APT::FTPArchive::SourceOverride",
			     SOverride.c_str());


   SourcesWriter Sources(_config->Find("APT::FTPArchive::DB"),Override,SOverride);
   if (_error->PendingError() == true)
      return false;

   if (CmdL.FileSize() >= 4)
      Sources.PathPrefix = CmdL.FileList[3];


   if (Sources.RecursiveScan(CmdL.FileList[1]) == false)
      return false;

   return true;
}
