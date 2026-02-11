hard_link_count(const path& p, system::error_code* ec)
  {
#   ifdef BOOST_POSIX_API

    struct stat path_stat;
    return error(::stat(p.c_str(), &path_stat)!= 0,
                  p, ec, "boost::filesystem::hard_link_count")
           ? 0
           : static_cast<boost::uintmax_t>(path_stat.st_nlink);

#   else


    BY_HANDLE_FILE_INFORMATION info;
    handle_wrapper h(
      create_file_handle(p.c_str(), 0,
          FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, 0,
          OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0));
    return
      !error(h.handle == INVALID_HANDLE_VALUE,
              p, ec, "boost::filesystem::hard_link_count")
      && !error(::GetFileInformationByHandle(h.handle, &info)== 0,
                 p, ec, "boost::filesystem::hard_link_count")
           ? info.nNumberOfLinks
           : 0;
#   endif
  }
