Instance_COM_Initialize(int argc, char ** argv, char ** parsedCommand, int * argcPtr, char *** argvPtr)
{
#if !defined(__WIN32__) && !defined(ECERE_BOOTSTRAP)

   setvbuf(stdout, null, _IONBF, 0);
#endif
#if defined(__WIN32__)
   *parsedCommand = UTF16toUTF8(GetCommandLineW());
   *argvPtr = eSystem_New0(sizeof(char *) * 512);
   *argcPtr = Tokenize(*parsedCommand, 512,(void*)(char **)(*argvPtr), forArgsPassing);
#else
   *argcPtr = argc;
   *argvPtr = argv;
#endif
#if defined(__unix__)
   if(!__thisModule && argv)
   {
      getcwd(exeLocation, MAX_LOCATION);
      PathCat(exeLocation, argv[0]);
   }
#endif
}
