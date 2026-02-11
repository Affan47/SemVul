new_language(const Config & config, ParmStr lang)
  {
    if (!lang)
      return get_cache_data(&language_cache, &config, config.retrieve("lang"));
    else
      return get_cache_data(&language_cache, &config, lang);
  }
