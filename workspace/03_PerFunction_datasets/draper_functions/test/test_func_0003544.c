m_get_status(system::error_code* ec) const
  {
    if (!status_known(m_status))
    {


      if (status_known(m_symlink_status)
        && !is_symlink(m_symlink_status))
      {
        m_status = m_symlink_status;
        if (ec != 0) ec->clear();
      }
      else m_status = detail::status(m_path, ec);
    }
    else if (ec != 0) ec->clear();
    return m_status;
  }
