DoShell(CommandLine &CmdL)
{
   for (const char **I = CmdL.FileList + 1; *I != 0; I += 2)
   {
      if (I[1] == 0 || strlen(I[1]) == 0)
	 return _error->Error(_("Arguments not in pairs"));

      string key = I[1];
      if (key.end()[-1] == '/')
	 key.append("d");

      if (_config->ExistsAny(key.c_str()))
	 cout << *I << "='" <<
	         SubstVar(_config->FindAny(key.c_str()),"'","'\\''") << '\'' << endl;

   }

   return true;
}
