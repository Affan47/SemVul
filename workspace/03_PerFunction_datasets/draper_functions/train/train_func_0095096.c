m_normalize()
  {
    if (m_pathname.empty()) return *this;

    path temp;
    iterator start(begin());
    iterator last(end());
    iterator stop(last--);
    for (iterator itr(start); itr != stop; ++itr)
    {

      if (itr->native().size() == 1
        && (itr->native())[0] == dot
        && itr != start
        && itr != last) continue;


      if (!temp.empty()
        && itr->native().size() == 2
        && (itr->native())[0] == dot
        && (itr->native())[1] == dot)
      {
        string_type lf(temp.filename().native());
        if (lf.size() > 0
          && (lf.size() != 1
            || (lf[0] != dot
              && lf[0] != separator))
          && (lf.size() != 2
            || (lf[0] != dot
              && lf[1] != dot
#             ifdef BOOST_WINDOWS_API
              && lf[1] != colon
#             endif
               )
             )
          )
        {
          temp.remove_filename();

          if (temp.m_pathname.size() > 0
            && temp.m_pathname[temp.m_pathname.size()-1]
              == separator)
          {
            string_type::size_type rds(
              root_directory_start(temp.m_pathname, temp.m_pathname.size()));
            if (rds == string_type::npos
              || rds != temp.m_pathname.size()-1)
              { temp.m_pathname.erase(temp.m_pathname.size()-1); }
          }

          iterator next(itr);
          if (temp.empty() && ++next != stop
            && next == last && *last == dot_path) temp /= dot_path;
          continue;
        }
      }

      temp /= *itr;
    };

    if (temp.empty()) temp /= dot_path;
    m_pathname = temp.m_pathname;
    return *this;
  }
