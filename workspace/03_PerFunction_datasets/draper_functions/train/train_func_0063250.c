is_notebook_tag(const Tag::Ptr & tag)
    {
      std::string fullTagName = tag->name();
      return Glib::str_has_prefix(fullTagName,
                                  std::string(Tag::SYSTEM_TAG_PREFIX)
                                  + Notebook::NOTEBOOK_TAG_PREFIX);
    }
