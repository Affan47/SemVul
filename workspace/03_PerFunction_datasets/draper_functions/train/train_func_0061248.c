create_default_readonly_dict(StringEnumeration * els,
                                              Config & config)
  {
    CachePtr<Language> lang;
    PosibErr<Language *> res = new_language(config);
    if (res.has_err()) return res;
    lang.reset(res.data);
    lang->set_lang_defaults(config);
    RET_ON_ERR(create(els,*lang,config));
    return no_err;
  }
