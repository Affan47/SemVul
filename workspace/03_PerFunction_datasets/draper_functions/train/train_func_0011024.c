load_theme_element(
      TreeHandler *pConfig,
      const Glib::RefPtr<Gnome::Glade::Xml>& refGlade,
      MainWindow *pWindow,
      xmlNode    *element)
{

  if(!strcmp((char*)element->name, "element"))
  {
    string id       = Utils::Xml::get_property(element, "id");
    string value    = Utils::Xml::get_property(element, "value");
    string disabled = Utils::Xml::get_property(element, "disabled");

    if(id != "" && value != "")
    {
      if(disabled == "true")
        pConfig->setOverride(strtol(id.c_str(), NULL, 10), false);
      else
        pConfig->setOverride(strtol(id.c_str(), NULL, 10), true);

      ConfigLoader::fill_config(
            pConfig,
            refGlade,
            pWindow,
            atoi(id.c_str()),
            value.c_str());
    }

  }

}
