equivalent(const path& p1, const path& p2, system::error_code* ec)
  {
#   ifdef BOOST_POSIX_API
    struct stat s2;
    int e2(::stat(p2.c_str(), &s2));
    struct stat s1;
    int e1(::stat(p1.c_str(), &s1));

    if (e1 != 0 || e2 != 0)
    {


      error (e1 != 0 && e2 != 0, p1, p2, ec, "boost::filesystem::equivalent");
      return false;
    }


    return  s1.st_dev == s2.st_dev && s1.st_ino == s2.st_ino


        && s1.st_size == s2.st_size && s1.st_mtime == s2.st_mtime;

#   else


    handle_wrapper h2(
      create_file_handle(
          p2.c_str(),
          0,
          FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
          0,
          OPEN_EXISTING,
          FILE_FLAG_BACKUP_SEMANTICS,
          0));

    handle_wrapper h1(
      create_file_handle(
          p1.c_str(),
          0,
          FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
          0,
          OPEN_EXISTING,
          FILE_FLAG_BACKUP_SEMANTICS,
          0));

    if (h1.handle == INVALID_HANDLE_VALUE
      || h2.handle == INVALID_HANDLE_VALUE)
    {


      error(h1.handle == INVALID_HANDLE_VALUE
        && h2.handle == INVALID_HANDLE_VALUE, p1, p2, ec,
          "boost::filesystem::equivalent");
      return false;
    }


    BY_HANDLE_FILE_INFORMATION info1, info2;

    if (error(!::GetFileInformationByHandle(h1.handle, &info1),
      p1, p2, ec, "boost::filesystem::equivalent"))
        return  false;

    if (error(!::GetFileInformationByHandle(h2.handle, &info2),
      p1, p2, ec, "boost::filesystem::equivalent"))
        return  false;


      return
        info1.dwVolumeSerialNumber == info2.dwVolumeSerialNumber
        && info1.nFileIndexHigh == info2.nFileIndexHigh
        && info1.nFileIndexLow == info2.nFileIndexLow
        && info1.nFileSizeHigh == info2.nFileSizeHigh
        && info1.nFileSizeLow == info2.nFileSizeLow
        && info1.ftLastWriteTime.dwLowDateTime
          == info2.ftLastWriteTime.dwLowDateTime
        && info1.ftLastWriteTime.dwHighDateTime
          == info2.ftLastWriteTime.dwHighDateTime;

#   endif
  }
