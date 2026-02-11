push_back(const Status & status_)
    {

      if (!status_.isSet())
        return;

      if (!status_.isVersioned())
      {


        apr_finfo_t finfo;
        Pool pool;
        apr_status_t apr_status = apr_stat(
                                    &finfo, status_.path(), APR_FINFO_TYPE, pool);


        if (apr_status != APR_SUCCESS)
          return;

        hasUnversioned = true;

        if (APR_DIR == finfo.filetype)
          hasDirs = true;
        else
          hasFiles = true;

      }
      else
      {
        hasVersioned = true;
        if (Url::isValid(status_.path()))
          hasUrl = true;
        else
          hasLocal = true;

        if (svn_node_dir == status_.entry().kind())
          hasDirs = true;
        else
          hasFiles = true;
      }


      targets.push_back(status_.path());
      status.push_back(status_);
    }
  }
