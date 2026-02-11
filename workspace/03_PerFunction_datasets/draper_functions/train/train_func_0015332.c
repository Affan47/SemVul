revpropget(const char *propName,
                     const Path &path,
                     const Revision &revision)
  {
    Pool pool;

    svn_string_t *propval;
    svn_revnum_t revnum;
    svn_error_t * error =
      svn_client_revprop_get(propName,
                             &propval,
                             path.c_str(),
                             revision.revision(),
                             &revnum,
                             *m_context,
                             pool);
    if (error != NULL)
    {
      throw ClientException(error);
    }


    if (propval == NULL)
      return std::pair<svn_revnum_t,std::string> (0, std::string());

    return std::pair<svn_revnum_t,std::string> (revnum, std::string(propval->data));
  }
