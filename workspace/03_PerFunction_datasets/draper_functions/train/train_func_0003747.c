DumpToString(const TemplateDictionary& dict) {

    if (dict.parent_dict_ == NULL) {
      DumpGlobals();
    }


    if (dict.template_global_dict_ && !dict.template_global_dict_->Empty()) {
      DumpTemplateGlobals(*dict.template_global_dict_);
    }

    DumpDictionary(dict);
  }
