filenameToUrl(const StringC &filename,
					 const Location &loc,
					 StringC &url)
{
#ifdef SP_MSDOS_FILENAMES
  if (filename.size() >= 3 && filename[1] == ':'
      && (('a' <= filename[0] && filename[0] <= 'z')
	  || ('A' <= filename[0] && filename[0] <= 'Z'))
      && (filename[2] == '/' || filename[2] == '\\')) {
    url += "file://";
    url += filename;
    return 1;
  }
#endif
  for (size_t i = 0; i < filename.size(); i++) {
    if (filename[i] == '/'
#ifdef SP_MSDOS_FILENAMES
        || filename[i] == '\\'
#endif
	) {
      url += '/';
    }
    else
      url += urlEncode(filename[i]);
  }
  return 1;
}
