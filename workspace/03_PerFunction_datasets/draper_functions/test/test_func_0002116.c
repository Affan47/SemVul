OpenTableFile(string &rule, const char *dir, string &path)
{

   path = dir;
   int istart = (int)path.size();
   path += rule + ".table";

   for (unsigned int i=istart; i<path.size(); i++)
      if (path[i] == '/' || path[i] == '\\') path[i] = '_';
   return fopen(path.c_str(), "rt");
}
