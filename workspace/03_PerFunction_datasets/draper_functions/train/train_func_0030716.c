beginObject(const std::string& name, const std::string& type)
    {
        ++_level;
        log_debug("beginObject, level=" << _level);
    }
