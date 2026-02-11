GLEReadFileBinaryGZIP(const string& name, std::vector<GLEBYTE>* contents) {
#ifdef HAVE_LIBZ
   gzFile file = gzopen(name.c_str(), "rb");
   if (file == 0) {
      return false;
   }
   bool returnCode = true;
   const int GLE_READ_GZIP_BUFFER_SIZE = 100000;
   char* buffer = new char[GLE_READ_GZIP_BUFFER_SIZE];
   bool done = false;
   while (!done) {
      int result = gzread(file, (voidp)buffer, GLE_READ_GZIP_BUFFER_SIZE);
      if (result == -1) {
         done = true;
         returnCode = false;
      } else if (result == 0) {
         done = true;
      } else {
         contents->reserve(contents->size() + result);
         for (int i = 0; i < result; ++i) {
            contents->push_back(buffer[i]);
         }
      }
   }
   delete[] buffer;
   gzclose(file);
   return returnCode;
#else
   return false;
#endif
}
