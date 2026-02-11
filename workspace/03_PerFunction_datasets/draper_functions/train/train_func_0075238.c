handleUndef(std::list<std::string> &configurations) const
{
    if (_settings && !_settings->userUndefs.empty()) {
        for (std::list<std::string>::iterator cfg = configurations.begin(); cfg != configurations.end();) {
            bool undef = false;
            for (std::set<std::string>::const_iterator it = _settings->userUndefs.begin(); it != _settings->userUndefs.end(); ++it) {
                if (*it == *cfg)
                    undef = true;
                else if (cfg->compare(0,it->length(),*it)==0 && cfg->find_first_of(";=") == it->length())
                    undef = true;
                else if (cfg->find(";" + *it) == std::string::npos)
                    ;
                else if (cfg->find(";" + *it + ";") != std::string::npos)
                    undef = true;
                else if (cfg->find(";" + *it + "=") != std::string::npos)
                    undef = true;
                else if (cfg->find(";" + *it) + it->size() + 1U == cfg->size())
                    undef = true;
            }

            if (undef)
                configurations.erase(cfg++);
            else
                ++cfg;
        }
    }
}
