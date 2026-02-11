GetLanguageCode()
{
  std::string code;

  char* string = XBMC->GetDVDMenuLanguage();

  if(string != NULL) {
    code = string;
    Log(DEBUG, "Possible leak caused by workaround in %s", __FUNCTION__);
#if 0
    XBMC->FreeString(string);
#endif
  }

  return code;
}
