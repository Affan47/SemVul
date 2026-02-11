remove(const path& p, error_code* ec)
  {
    error_code tmp_ec;
    file_type type = query_file_type(p, &tmp_ec);
    if (error(type == status_error, tmp_ec, p, ec,
        "boost::filesystem::remove"))
      return false;


    return remove_file_or_directory(p, type, ec);
  }
