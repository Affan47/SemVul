portable_directory_name(const std::string & name)
    {
      return
        name == "."
        || name == ".."
        || (portable_name(name)
          && name.find('.') == std::string::npos);
    }
