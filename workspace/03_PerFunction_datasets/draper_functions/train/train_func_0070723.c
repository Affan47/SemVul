ProcessCommandLANG(ICECAdapter *parser, const string &command, string &arguments)
{
  if (command == "lang")
  {
    CStdString strDev;
    if (GetWord(arguments, strDev))
    {
      int iDev = atoi(strDev);
      if (iDev >= 0 && iDev < 15)
      {
        CStdString strLog;
        cec_menu_language language;
        if (parser->GetDeviceMenuLanguage((cec_logical_address) iDev, &language))
          strLog.Format("menu language '%s'", language.language);
        else
          strLog = "failed!";
        PrintToStdOut(strLog);
        return true;
      }
    }
  }

  return false;
}
