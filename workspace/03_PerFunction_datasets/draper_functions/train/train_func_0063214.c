localStatus(const char * path,
              const bool descend,
              const bool get_all,
              const bool update,
              const bool no_ignore,
              Context * context,
              const bool ignore_externals)
  {
    svn_error_t *error;
    StatusEntries entries;
    svn_revnum_t revnum;
    Revision rev(Revision::HEAD);
    Pool pool;

    error = svn_client_status2(
              &revnum,
              path,
              rev,
              statusEntriesFunc,
              &entries,
              descend,
              get_all,
              update,
              no_ignore,
              ignore_externals,
              *context,
              pool);

    if (error!=NULL)
      throw ClientException(error);

    return entries;
  }
