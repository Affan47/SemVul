absolute(const path& p, const path& base)
  {


    path abs_base(base.is_absolute() ? base : absolute(base));


    path p_root_name (p.root_name());
    path base_root_name (abs_base.root_name());
    path p_root_directory (p.root_directory());

    if (p.empty())
      return abs_base;

    if (!p_root_name.empty())
    {
      if (p_root_directory.empty())
        return p_root_name / abs_base.root_directory()
        / abs_base.relative_path() / p.relative_path();

    }

    else if (!p_root_directory.empty())
    {
#     ifdef BOOST_POSIX_API

      if (base_root_name.empty())
        return p;
#     endif
      return base_root_name / p;
    }

    else
    {
      return abs_base / p;
    }

    return p;
  }
