onSimplePrompt(svn_auth_cred_simple_t **cred,
                   void *baton,
                   const char *realm,
                   const char *username,
                   svn_boolean_t _may_save,
                   apr_pool_t *pool)
    {
      Data * data = NULL;
      SVN_ERR(getData(baton, &data));

      bool may_save = _may_save != 0;
      if (!data->retrieveLogin(username, realm, may_save))
        return svn_error_create(SVN_ERR_CANCELLED, NULL, "");

      svn_auth_cred_simple_t* lcred = (svn_auth_cred_simple_t*)
                                      apr_palloc(pool, sizeof(svn_auth_cred_simple_t));


      lcred->password = data->getPassword();
      lcred->username = data->getUsername();


      lcred->may_save = may_save;
      *cred = lcred;

      return SVN_NO_ERROR;
    }
