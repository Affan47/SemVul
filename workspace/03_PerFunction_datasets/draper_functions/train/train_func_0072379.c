dump_profile(Profile *profile) {
    DBG(1, form("KCemu/Preferences",
                "Preferences::dump_profile(): dumping profile '%s' (flags: %c%c)\n",
                profile->get_name(),
                profile->is_changed() ? 'C' : 'c',
                profile->is_deleted() ? 'D' : 'd'));

    string path = get_profile_path(_usr_dir, profile->get_config_name());
    DBG(1, form("KCemu/Preferences",
                "Preferences::dump_profile(): path is '%s'\n",
                path.c_str()));

    list<string> *keys = profile->get_keys();
    for (list<string>::iterator it = keys->begin();it != keys->end();it++) {
        char *value = profile->get_encoded_value(*it);
        DBG(1, form("KCemu/Preferences",
                    "Preferences::dump_profile(): .. %s = %s\n",
                    (*it).c_str(), value));
        free(value);
    }
    DBG(1, form("KCemu/Preferences",
                "Preferences::dump_profile(): end.\n"));
}
