handleUnlinkedFile()
{
  if (!jalib::Filesystem::FileExists(_path)) {


    if (Util::strEndsWith(_path, DELETED_FILE_SUFFIX)) {
      _path.erase( _path.length() - strlen(DELETED_FILE_SUFFIX) );
      _type = FILE_DELETED;
    } else {
      JASSERT(_type == FILE_DELETED) (_path)
        .Text ("File not found on disk and yet the filename doesn't "
               "contain the suffix '(deleted)'");
    }
  } else if (Util::strStartsWith(jalib::Filesystem::BaseName(_path),
                                 ".nfs")) {
    JWARNING(access(_path.c_str(), W_OK) == 0) (JASSERT_ERRNO);
    JTRACE(".nfsXXXX: files that are unlink()'d but still in use by some process(es)")
      (_path);
    _type = FILE_DELETED;
  }
}
