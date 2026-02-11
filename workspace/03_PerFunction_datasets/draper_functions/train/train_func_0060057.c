processOption(AppChar opt, const AppChar *arg)
{
  switch (opt) {
  case 'h':

    normalizeFlags_ |= CopyEventHandler::normalizeOmittagHoist;
    break;
  case 'l':
    normalizeFlags_ |= CopyEventHandler::normalizeLower;
    break;
  case 'm':
    {
      Boolean found = 0;
      for (size_t i = 0; i < SIZEOF(normalizeTable); i++)
	if (tcscmp(normalizeTable[i].name, arg) == 0) {
	  found = 1;
	  normalizeFlags_ |= normalizeTable[i].flag;
	  break;
	}
      if (!found) {
	message(SpamMessages::invalidMarkupArgument,
		StringMessageArg(convertInput(arg)));

      }
    }
    break;
  case 'o':
    outputEntity_ = convertInput(arg);
    break;
  case 'p':
    if (normalizeFlags_ & CopyEventHandler::normalizeIncludeProlog)
      normalizeFlags_ |= CopyEventHandler::normalizeExpandProlog;
    else
      normalizeFlags_ |= CopyEventHandler::normalizeIncludeProlog;
    break;
  case 'r':
    rawOutput_ = 1;
    break;
  case 'x':
    if (normalizeFlags_ & CopyEventHandler::normalizeExpand)
      normalizeFlags_ |= CopyEventHandler::normalizeExpandAll;
    else
      normalizeFlags_ |= CopyEventHandler::normalizeExpand;
    break;
  default:
    ParserApp::processOption(opt, arg);
    break;
  }
}
