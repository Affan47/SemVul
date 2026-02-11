GetLinkerLanguage(const char* config, cmTarget *head)
{
  cmTarget *headTarget = head ? head : this;
  const char* lang = this->GetLinkClosure(config, headTarget)
                                                    ->LinkerLanguage.c_str();
  return *lang? lang : 0;
}
