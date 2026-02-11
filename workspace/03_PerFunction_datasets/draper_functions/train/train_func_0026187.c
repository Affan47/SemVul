reservedErrorCheck(const TSourceLoc& line, const TString& identifier)
{
   if (!symbolTable.atBuiltInLevel())
   {
      if (identifier.substr(0, 3) == TString("gl_"))
      {
         error(line, "reserved built-in name", "gl_", "");
         return true;
      }
      if (identifier.find("__") != TString::npos)
      {
         infoSink.info.message(EPrefixWarning, "Two consecutive underscores are reserved for future use.", line);
         return false;
      }
   }

   return false;
}
