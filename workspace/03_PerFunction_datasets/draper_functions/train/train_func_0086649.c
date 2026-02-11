propget(const char *propName,
                  const Path &path,
                  const Revision &revision,
                  bool recurse)
  {
    Pool pool;

    apr_hash_t *props;
    svn_error_t * error =
      svn_client_propget(&props,
                         propName,
                         path.c_str(),
                         revision.revision(),
                         recurse,
                         *m_context,
                         pool);
    if (error != NULL)
    {
      throw ClientException(error);
    }

    PathPropertiesMapList path_prop_map_list;


    apr_hash_index_t *hi;
    for (hi = apr_hash_first(pool, props); hi;
         hi = apr_hash_next(hi))
    {
      PropertiesMap prop_map;

      const void *key;
      void *val;

      apr_hash_this(hi, &key, NULL, &val);

      prop_map [std::string(propName)] = std::string(((const svn_string_t *)val)->data);

      path_prop_map_list.push_back(PathPropertiesMapEntry((const char *)key, prop_map));
    }

    return path_prop_map_list;
  }
