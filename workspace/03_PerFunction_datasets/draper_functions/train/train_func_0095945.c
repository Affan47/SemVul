diff(const Path & tmpPath, const Path & path,
               const Revision & revision1, const Revision & revision2,
               const bool recurse, const bool ignoreAncestry,
               const bool noDiffDeleted) throw(ClientException)
  {
    Pool pool;
    svn_error_t * error;
    apr_status_t status;
    apr_file_t * outfile = NULL;
    const char * outfileName = NULL;
    apr_file_t * errfile = NULL;
    const char * errfileName = NULL;
    apr_array_header_t * options;
    svn_stringbuf_t * stringbuf;


    options = apr_array_make(pool, 0, 0);


    error = svn_io_open_unique_file(&outfile, &outfileName,
                                    tmpPath.c_str(), ".tmp",
                                    false, pool);

    if (error != NULL)
    {
      diffCleanup(outfile, outfileName, errfile, errfileName, pool);
      throw ClientException(error);
    }


    error = svn_io_open_unique_file(&errfile, &errfileName,
                                    tmpPath.c_str(), ".tmp",
                                    false, pool);

    if (error != NULL)
    {
      diffCleanup(outfile, outfileName, errfile, errfileName, pool);
      throw ClientException(error);
    }


    error = svn_client_diff(options,
                            path.c_str(), revision1.revision(),
                            path.c_str(), revision2.revision(),
                            recurse, ignoreAncestry, noDiffDeleted,
                            outfile, errfile,
                            *m_context,
                            pool);

    if (error != NULL)
    {
      diffCleanup(outfile, outfileName, errfile, errfileName, pool);
      throw ClientException(error);
    }


    status = apr_file_close(outfile);
    if (status)
    {
      diffCleanup(outfile, outfileName, errfile, errfileName, pool);
      fail(pool, status, "failed to close '%s'", outfileName);
    }

    status = apr_file_open(&outfile, outfileName, APR_READ, APR_OS_DEFAULT, pool);
    if (status)
    {
      diffCleanup(outfile, outfileName, errfile, errfileName, pool);
      fail(pool, status, "failed to open '%s'", outfileName);
    }


    error = svn_stringbuf_from_aprfile(&stringbuf, outfile, pool);

    if (error != NULL)
    {
      diffCleanup(outfile, outfileName, errfile, errfileName, pool);
      throw ClientException(error);
    }

    diffCleanup(outfile, outfileName, errfile, errfileName, pool);
    return stringbuf->data;
  }
