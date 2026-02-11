mkdir(const Path & path) throw(ClientException)
  {
    Pool pool;
    Targets targets(path.c_str());

    svn_client_commit_info_t *commit_info = NULL;
    svn_error_t * error =
      svn_client_mkdir(&commit_info,
                       const_cast<apr_array_header_t*>
                       (targets.array(pool)),
                       *m_context, pool);

    if (error != NULL)
      throw ClientException(error);
  }
