tags()
  {
    for (unsigned int i=1; i<m_log_base; ++i)
      m_log_tags.insert(i);

    return *this;
  }
