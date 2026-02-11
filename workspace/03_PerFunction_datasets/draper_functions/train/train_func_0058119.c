parseResource(ArArgumentBuilder *arg,
				                                 char *errorBuffer,
				                                 size_t errorBufferLen,
                                         const char *logPrefix,
                                         bool isQuiet)
{

  if (arg == NULL) {
    ArLog::log(ArLog::Normal,
               "%sArConfigArg::parseResource(), invalid input",
               ((logPrefix != NULL) ? logPrefix : ""));
    return false;
  }

  if (arg->getArgc() == 0) {

    return false;
  }

  if (arg->getArgc() <= RESOURCE_INDEX_OF_DESCRIPTION) {
    ArLog::log(ArLog::Normal,
               "%sArConfigArg::parseResource(), invalid input, too few args (%i)",
               ((logPrefix != NULL) ? logPrefix : ""),
               arg->getArgc());
    return false;
  }

  if (ArUtil::isStrEmpty(arg->getArg(RESOURCE_INDEX_OF_ARG_NAME))) {
    ArLog::log(ArLog::Normal,
               "%sArConfigArg::parseResource(), empty name",
               ((logPrefix != NULL) ? logPrefix : ""));
  }

 char buf[MAX_RESOURCE_ARG_TEXT_LENGTH];

  if (arg->getArgc() > RESOURCE_INDEX_OF_DESCRIPTION) {
    if (parseResourceArgText(arg->getArg(RESOURCE_INDEX_OF_DESCRIPTION),
                             buf,
                             MAX_RESOURCE_ARG_TEXT_LENGTH)) {
      myDescription = buf;
    }
  }

  if (arg->getArgc() > RESOURCE_INDEX_OF_EXTRA) {
    if (parseResourceArgText(arg->getArg(RESOURCE_INDEX_OF_EXTRA),
                           buf,
                           MAX_RESOURCE_ARG_TEXT_LENGTH)) {
      myExtraExplanation = buf;
    }
  }

  if (arg->getArgc() > RESOURCE_INDEX_OF_DISPLAY) {
    if (parseResourceArgText(arg->getArg(RESOURCE_INDEX_OF_DISPLAY),
                           buf,
                           MAX_RESOURCE_ARG_TEXT_LENGTH)) {
      myDisplayName = buf;
    }
  }

  if (arg->getArgc() > RESOURCE_INDEX_OF_NEW) {
    if (parseResourceArgText(arg->getArg(RESOURCE_INDEX_OF_NEW),
                             buf,
                             MAX_RESOURCE_ARG_TEXT_LENGTH)) {
      if (ArUtil::strcasecmp(buf, NEW_RESOURCE_TAG) == 0) {
        myIsTranslated = false;
      }
      else {
        myIsTranslated = true;
      }
    }
  }

  return true;

}
