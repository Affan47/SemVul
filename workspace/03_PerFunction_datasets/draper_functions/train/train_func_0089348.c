add(ModuleDesc* m_i, Glib::Module* m_h, PluginDescriptor* d_h) {
    if(this->find(m_i->name)) return false;

    module_t_ module;
    module.module = m_h;
    unsigned int sane_count = 1024;

    for(PluginDescriptor* p = d_h;(p->kind) && (p->name) && (p->instance);++p) {
      if(--sane_count == 0) break;
      if(!issane(p->kind)) break;
      if(!issane(p->name)) break;
      if(!issane(p->description)) break;

      descriptor_t_ d;
      d.desc_m = p;
      d.desc_i.name = p->name; d.desc_i.kind = p->kind; d.desc_i.version = p->version;
      if(p->description) d.desc_i.description = p->description;
      d.desc_i.priority = ARC_PLUGIN_DEFAULT_PRIORITY;
      for(std::list<PluginDesc>::iterator pd = m_i->plugins.begin();
                         pd != m_i->plugins.end();++pd) {
        if((pd->name == d.desc_i.name) &&
           (pd->kind == d.desc_i.kind) &&
           (pd->version == d.desc_i.version)) {
          d.desc_i = *pd; break;
        };
      };

      module.plugins.push_back(d);
    };

    module_t_& module_r = ((*this)[m_i->name] = module);


    for(std::list<descriptor_t_>::iterator p = module_r.plugins.begin();
                             p != module_r.plugins.end(); ++p) {

      std::list< std::pair<descriptor_t_*,module_t_*> >::iterator pp = plugins_.begin();
      for(; pp != plugins_.end(); ++pp) {
        if((*p).desc_i.priority > (*pp).first->desc_i.priority) break;
      };
      plugins_.insert(pp,std::pair<descriptor_t_*,module_t_*>(&(*p),&module_r));
    };
    return true;
  }
