Configuration(std::string Message)
{
   char ProgStr[100];

   if (pkgAcqMethod::Configuration(Message) == false)
      return false;

   snprintf(ProgStr, sizeof ProgStr, "Acquire::%s::Timeout", Prog);
   TimeOut = _config->FindI(ProgStr,TimeOut);
   snprintf(ProgStr, sizeof ProgStr, "Acquire::%s::Options", Prog);
   RshOptions = _config->Tree(ProgStr);

   return true;
}
