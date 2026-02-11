db_check_entry (gnutls_datum_t & session_data) const
  {
    int ret = gnutls_db_check_entry (s, session_data);

    if (ret != 0)
      return true;
    return false;
  }
