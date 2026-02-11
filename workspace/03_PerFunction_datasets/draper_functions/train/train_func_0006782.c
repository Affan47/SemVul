buildPath( string & dir, string & filename, string & outname )
{
   size_t len = dir.length();

   if ( len == 0 ) {
      outname = filename;
   }
   else {
      outname = dir;
#if defined(WIN32)
      if ( dir[len-1] != '\\' && dir[len-1] != '/' ) outname += "\\";
#else
      if ( dir[len-1] != '/' ) outname += "/";
#endif
      outname += filename;
   }

   if ( outname.length() >= PATH_MAX ) {
      cerr << "File name is too long!" << endl;
      exit(1);
   }
}
