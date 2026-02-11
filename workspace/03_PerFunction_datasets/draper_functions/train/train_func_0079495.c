run(int argc, AppChar **argv)
{
#ifdef _MSC_VER
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
#endif
#ifdef SP_ANSI_LIB
  try {
#endif
  int ret = init(argc, argv);
  if (ret)
    return ret;
  int firstArg;
  ret = processOptions(argc, argv, firstArg);
  if (ret)
    return ret;
  ret = processArguments(argc - firstArg, argv + firstArg);
  progName = 0;
  return ret;
#ifdef SP_ANSI_LIB
  }
catch (
#ifndef SP_NO_STD_NAMESPACE
       std::
#endif
	    bad_alloc) {
#ifdef SP_FANCY_NEW_HANDLER
    outOfMemory(0);
#else
    outOfMemory();
#endif
  }
  return 1;
#endif
}
