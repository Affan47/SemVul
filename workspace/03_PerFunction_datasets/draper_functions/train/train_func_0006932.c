GenerateTemporaryFileTemplate(const char *basename)
{
   std::string out;
   std::string tmpdir = GetTempDir();
   strprintf(out,  "%s/%s.XXXXXX", tmpdir.c_str(), basename);
   return strdup(out.c_str());
}
