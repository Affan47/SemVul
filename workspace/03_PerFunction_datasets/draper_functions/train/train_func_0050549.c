addFile(const string& name) {

  Assert(md5BlockLength != 0);

  Paranoid(name.length() > 0);


  string::size_type pathLen = name.rfind(SPLITSEP);
  string fileUri("file:");
  string path, nameRest;
  if (pathLen == string::npos) {
    size_t splitAfter = 0;
#   if WINDOWS

    if (name.length() > 1 && isalpha(name[0]) && name[1] == ':')
      splitAfter = 2;
    if (name.length() > splitAfter && name[splitAfter] == '\\') {

      ++splitAfter;
    } else if (name.length() > splitAfter + 1
               && name[splitAfter] == '.' && name[splitAfter + 1] == '\\') {

      splitAfter += 2;
    }
#   else

    if (name[0] == DIRSEP) splitAfter = 1;
#   endif
    path.assign(name, 0, splitAfter);
    fileUri += path;
    nameRest.assign(name, splitAfter, string::npos);
  } else {

    path.assign(name, 0, pathLen + 1);
    fileUri.append(name, 0, pathLen + 1);

    nameRest.assign(name, pathLen + sizeof(SPLITSEP) - 1, string::npos);
  }
  compat_swapFileUriChars(fileUri);
  ConfigFile::quote(fileUri);


  static string emptylabel;
  LocationPath tmp(path, emptylabel, fileUri);
  LocationPathSet::iterator i = locationPaths.find(tmp);
  if (i == locationPaths.end())
    i = locationPaths.insert(tmp).first;
  Paranoid(i != locationPaths.end());


  FilePart fp(i, nameRest, fileInfo.st_size, fileInfo.st_mtime);
  files.push_back(fp);
}
