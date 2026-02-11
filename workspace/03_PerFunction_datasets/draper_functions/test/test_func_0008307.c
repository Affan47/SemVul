display_print (displayd * display)
{
  ggobid *gg;
  gg = display->ggobi;

  if (gg->printOptions == NULL) {
    gg->printOptions = getDefaultPrintOptions (NULL);
  }

  if (DefaultPrintHandler.callback)
    (*DefaultPrintHandler.callback) (gg->printOptions, display,
                                     display->ggobi, &DefaultPrintHandler);
}
