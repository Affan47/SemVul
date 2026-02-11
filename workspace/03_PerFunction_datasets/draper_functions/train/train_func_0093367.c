LoadFileList(string const &Dir, string const &File)
{
   char *RealPath = NULL;


   if (InternalPrefix.empty() == true)
   {
      if ((RealPath = realpath(Dir.c_str(),NULL)) == 0)
	 return _error->Errno("realpath",_("Failed to resolve %s"),Dir.c_str());
      InternalPrefix = RealPath;
      free(RealPath);
   }

   Owner = this;
   FILE *List = fopen(File.c_str(),"r");
   if (List == 0)
      return _error->Errno("fopen",_("Failed to open %s"),File.c_str());


   char Line[1000];
   char *FileStart;
   if (Dir.empty() == true || Dir.end()[-1] != '/')
      FileStart = Line + snprintf(Line,sizeof(Line),"%s/",Dir.c_str());
   else
      FileStart = Line + snprintf(Line,sizeof(Line),"%s",Dir.c_str());
   while (fgets(FileStart,sizeof(Line) - (FileStart - Line),List) != 0)
   {
      char *FileName = _strstrip(FileStart);
      if (FileName[0] == 0)
	 continue;

      if (FileName[0] != '/')
      {
	 if (FileName != FileStart)
	    memmove(FileStart,FileName,strlen(FileStart));
	 FileName = Line;
      }

#if 0
      struct stat St;
      int Flag = FTW_F;
      if (stat(FileName,&St) != 0)
	 Flag = FTW_NS;
#endif

      if (ScannerFile(FileName, false) != 0)
	 break;
   }

   fclose(List);
   return true;
}
