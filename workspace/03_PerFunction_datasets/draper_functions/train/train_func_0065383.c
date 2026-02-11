get_addin_category_name(gnote::AddinCategory category)
  {
    switch(category) {
      case gnote::ADDIN_CATEGORY_FORMATTING:

        return _("Formatting");
      case gnote::ADDIN_CATEGORY_DESKTOP_INTEGRATION:

        return _("Desktop integration");
      case gnote::ADDIN_CATEGORY_TOOLS:

        return _("Tools");
      case gnote::ADDIN_CATEGORY_SYNCHRONIZATION:

        return _("Synchronization");
      case gnote::ADDIN_CATEGORY_UNKNOWN:
      default:

        return _("Unknown");
    }
  }
