pilMsgEnableLog(PilMsgSeverity severity)
{
  char *timeLabel;

  if (logfilePointer) {


    if (pilMsgCloseLog() == EXIT_FAILURE) {
      return EXIT_FAILURE;
    }
  }
  if (severity != PIL_MSG_OFF) {
    logMinLevel = severity;

    if ((logfilePointer = fopen(logfileName, "w")) == NULL) {
      return EXIT_FAILURE;
    }


    timeLabel = pilDateGetISO8601();
    fprintf(logfilePointer, "\n");
    fprintf(logfilePointer, "Start time     : %s\n", timeLabel);
    fprintf(logfilePointer, "Recipe name    : %s\n", recipeName);
    fprintf(logfilePointer, "Severity level : ");
    switch(severity) {
      case PIL_MSG_DEBUG   : fprintf(logfilePointer, DEBUG_STRING); break;
      case PIL_MSG_INFO    : fprintf(logfilePointer, INFO_STRING); break;
      case PIL_MSG_WARNING : fprintf(logfilePointer, WARNING_STRING); break;
      case PIL_MSG_ERROR   : fprintf(logfilePointer, ERROR_STRING); break;
      default              : ;
    }
    fprintf(logfilePointer, "\n\n");
  }
  return EXIT_SUCCESS;
}
