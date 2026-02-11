GetFileInfo(std::string const &FileName, bool const &DoControl, bool const &DoContents,
				bool const &GenContentsOnly, bool const &DoMD5, bool const &DoSHA1,
				bool const &DoSHA256, 	bool const &DoSHA512,
                          bool const &checkMtime)
{
	this->FileName = FileName;

	if (GetCurStat() == false)
   {
		return false;
   }
   OldStat = CurStat;

	if (GetFileStat(checkMtime) == false)
	{
		delete Fd;
		Fd = NULL;
		return false;
	}


    if (checkMtime == true && OldStat.mtime != CurStat.mtime)
        CurStat.Flags = FlSize;

	Stats.Bytes += CurStat.FileSize;
	Stats.Packages++;

	if ((DoControl && LoadControl() == false)
		|| (DoContents && LoadContents(GenContentsOnly) == false)
		|| (DoMD5 && GetMD5(false) == false)
		|| (DoSHA1 && GetSHA1(false) == false)
		|| (DoSHA256 && GetSHA256(false) == false)
		|| (DoSHA512 && GetSHA512(false) == false)
           )
	{
		delete Fd;
		Fd = NULL;
		delete DebFile;
		DebFile = NULL;
		return false;
	}

	delete Fd;
	Fd = NULL;
	delete DebFile;
	DebFile = NULL;

   return true;
}
