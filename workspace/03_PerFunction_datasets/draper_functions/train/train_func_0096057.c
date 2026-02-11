attach_engine(
      string engine_name,
      string category,
      TreeHandler* config,
      bool override)
{

  Engine *engine = engines;
  while(engine != NULL)
  {
    if(engine->name == engine_name)
    {
      config->attachEngine(xmlDocGetRootElement(engine->doc), (char*)category.c_str());
      if(override)
        config->setEngineOverride(category, true);
      break;
    }
    engine = engine->next;
  }
}
