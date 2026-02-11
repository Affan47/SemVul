Set(const std::string& name, const std::string& value, bool overwrite) {
    if(!overwrite) {
      if(getenv(name.c_str())) return false;
    };
    for(std::list<TrickEnvRecord>::iterator r = records_.begin();
                                                r != records_.end(); ++r) {
      if(r->name_ == name) {
        return r->Set(value);
      };
    };

    TrickEnvRecord rec(name);
    if(!rec.Set(value)) return false;
    records_.push_back(rec);
    return true;
  }
