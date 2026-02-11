parent_path() const
  {
   size_type end_pos(m_parent_path_end());
   return end_pos == string_type::npos
     ? path()
     : path(m_pathname.c_str(), m_pathname.c_str() + end_pos);
  }
