visit_changed(ProfileVisitor &visitor) {
    DBG(1, form("KCemu/Preferences",
                "Preferences::visit_changed(): Start visiting changed profiles:\n"));

    if (_default_profile->is_changed()) {
        DBG(1, form("KCemu/Preferences",
                    "Preferences::visit_changed(): ... default profile changed\n"));
        visitor.handle_profile(_default_profile);
    }

    for (profile_map_t::iterator it = _usr_profiles.begin();it != _usr_profiles.end();it++) {
        Profile *profile = (*it).second;
        if (profile->is_changed()) {
            DBG(1, form("KCemu/Preferences",
                        "Preferences::visit_changed(): ... system profile '%s' changed\n",
                        profile->get_name()));
            visitor.handle_profile(profile);
        }
    }

    for (profile_map_t::iterator it = _add_profiles.begin();it != _add_profiles.end();it++) {
        Profile *profile = (*it).second;
        if (profile->is_changed()) {
            DBG(1, form("KCemu/Preferences",
                        "Preferences::visit_changed(): ... user profile '%s' changed\n",
                        profile->get_name()));
            visitor.handle_profile(profile);
        }
    }

    DBG(1, form("KCemu/Preferences",
                "Preferences::visit_changed(): End visiting changed profiles.\n"));
}
