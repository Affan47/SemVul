localFilteredStatus(const char * path,
                      const StatusFilter & filter,
                      const bool descend,
                      const bool update,
                      StatusEntries & entries,
                      Context * context)
  {
    svn_error_t *error;
    svn_revnum_t revnum;
    Revision rev(Revision::HEAD);
    Pool pool;
    StatusBaton baton(filter, entries);

    error = svn_client_status2(
              &revnum,
              path,
              rev,
              filteredStatusFunc,
              &baton,
              descend,
              filter.showUnmodified,
              update,
              filter.showIgnored,
              !filter.showExternals,
              *context,
              pool);

    if (error!=NULL)
      throw ClientException(error);

    return revnum;
  }
