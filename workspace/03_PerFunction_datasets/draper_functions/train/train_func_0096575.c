DoDownloadFile(CommandLine &CmdL)
{
   if (CmdL.FileSize() <= 2)
      return _error->Error(_("Must specify at least one pair url/filename"));


   pkgAcquire Fetcher;
   AcqTextStatus Stat(ScreenWidth, _config->FindI("quiet",0));
   Fetcher.Setup(&Stat);
   std::string download_uri = CmdL.FileList[1];
   std::string targetfile = CmdL.FileList[2];
   std::string hash;
   if (CmdL.FileSize() > 3)
      hash = CmdL.FileList[3];
   new pkgAcqFile(&Fetcher, download_uri, hash, 0, "desc", "short-desc",
                  "dest-dir-ignored", targetfile);
   Fetcher.Run();
   bool Failed = false;
   if (AcquireRun(Fetcher, 0, &Failed, NULL) == false || Failed == true ||
	 FileExists(targetfile) == false)
      return _error->Error(_("Download Failed"));
   return true;
}
