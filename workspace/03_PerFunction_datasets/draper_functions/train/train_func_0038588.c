AddStatusFiles(std::vector<pkgIndexFile *> &List)
{
   if (StatusFile == 0)
   {
      if (_config->Find("edsp::scenario", "") == "stdin")
	 StatusFile = new edspIndex("stdin");
      else
	 StatusFile = new edspIndex(_config->FindFile("edsp::scenario"));
   }
   List.push_back(StatusFile);
   return true;
}
