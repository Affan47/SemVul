init(Config & config)
  {
    if (!config.have("norm-strict"))
      config.replace("norm-strict", "true");
    have_affix = lang->have_affix();
    validate_words = config.retrieve_bool("validate-words");
    validate_affixes = config.retrieve_bool("validate-affixes");
    clean_words = config.retrieve_bool("clean-words");
    skip_invalid_words = config.retrieve_bool("skip-invalid-words");
    clean_affixes = config.retrieve_bool("clean-affixes");
    if (config.have("encoding")) {
      RET_ON_ERR(iconv.setup(config, config.retrieve("encoding"), lang->charmap(),NormFrom));
    } else {
      RET_ON_ERR(iconv.setup(config, lang->data_encoding(), lang->charmap(), NormFrom));
    }
    brk[0] = ' ';
    if (!lang->special('-').any) brk[1] = '-';
    return no_err;
  }
