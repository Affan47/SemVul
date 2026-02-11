parseResourceArgName(ArArgumentBuilder *arg,
                                                           const char *logPrefix)
{
  std::string argName;

  if ((arg == NULL) ||
      (arg->getArgc() <= RESOURCE_INDEX_OF_ARG_NAME)) {

     ArLog::log(ArLog::Normal,
                "%sArConfigArg::parseResourceArgName() invalid input (%s)",
                ((logPrefix != NULL) ? logPrefix : ""),
                ((arg != NULL) ? arg->getFullString() : "NULL"));
    return argName;
  }

  char buf[MAX_RESOURCE_ARG_TEXT_LENGTH];

  if (parseResourceArgText(arg->getArg(RESOURCE_INDEX_OF_ARG_NAME),
                           buf,
                           MAX_RESOURCE_ARG_TEXT_LENGTH)) {
    argName = buf;
  }
  return argName;

}
