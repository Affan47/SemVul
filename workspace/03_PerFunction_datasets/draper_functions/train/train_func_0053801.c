ReadAppend(string File)
{
   if (_config->FindB("APT::Sources::Use-Deb822", false) == true)
   {
      int lines_parsed =ParseFileDeb822(File);
      if (lines_parsed < 0)
         return false;
      else if (lines_parsed > 0)
         return true;

   }
   return ParseFileOldStyle(File);
}
