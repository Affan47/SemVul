Start()
{

   string Method = _config->FindDir("Dir::Bin::Methods") + Access;
   if (FileExists(Method) == false)
   {
      _error->Error(_("The method driver %s could not be found."),Method.c_str());
      if (Access == "https")
	 _error->Notice(_("Is the package %s installed?"), "apt-transport-https");
      return false;
   }

   if (Debug == true)
      clog << "Starting method '" << Method << '\'' << endl;


   int Pipes[4] = {-1,-1,-1,-1};
   if (pipe(Pipes) != 0 || pipe(Pipes+2) != 0)
   {
      _error->Errno("pipe","Failed to create IPC pipe to subprocess");
      for (int I = 0; I != 4; I++)
	 close(Pipes[I]);
      return false;
   }
   for (int I = 0; I != 4; I++)
      SetCloseExec(Pipes[I],true);


   Process = ExecFork();
   if (Process == 0)
   {

      dup2(Pipes[1],STDOUT_FILENO);
      dup2(Pipes[2],STDIN_FILENO);
      SetCloseExec(STDOUT_FILENO,false);
      SetCloseExec(STDIN_FILENO,false);
      SetCloseExec(STDERR_FILENO,false);

      const char *Args[2];
      Args[0] = Method.c_str();
      Args[1] = 0;
      execv(Args[0],(char **)Args);
      cerr << "Failed to exec method " << Args[0] << endl;
      _exit(100);
   }


   InFd = Pipes[0];
   OutFd = Pipes[3];
   SetNonBlock(Pipes[0],true);
   SetNonBlock(Pipes[3],true);
   close(Pipes[1]);
   close(Pipes[2]);
   OutReady = false;
   InReady = true;


   if (WaitFd(InFd) == false ||
       ReadMessages() == false)
      return _error->Error(_("Method %s did not start correctly"),Method.c_str());

   RunMessages();
   if (OwnerQ != 0)
      SendConfiguration();

   return true;
}
