processOption(AppChar opt, const AppChar *arg)
{
  switch (opt) {
  case 't':
    {
      const AppChar *sub = tcschr(arg, SP_T('-'));
      size_t len = sub ? sub - arg : tcslen(arg);
      for (size_t i = 0;; i++) {
        if (i >= SIZEOF(outputTypeNames)) {
	  message(JadeMessages::unknownType, StringMessageArg(convertInput(arg)));
	  break;
	}
	if (tcsncmp(arg, outputTypeNames[i], len) == 0) {
	  outputType_ = OutputType(i);
	  break;
	}
      }
      if (sub) {
	StringC tem(convertInput(sub));
	StringC arg;
	for (size_t i = 0; i < tem.size(); i++) {
	  if (tem[i] == '-') {
	    if (arg.size())
	      outputOptions_.push_back(arg);
	    arg.resize(0);
	  }
	  else
	    arg += tem[i];
	}
	if (arg.size())
	  outputOptions_.push_back(arg);
      }
    }
    break;
  case 'o':
    if (*arg == 0)
      message(JadeMessages::emptyOutputFilename);
    else
      outputFilename_.assign(arg, tcslen(arg));
    break;
  default:
    DssslApp::processOption(opt, arg);
    break;
  }
}
