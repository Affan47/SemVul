resolve_hardware_alias (const std::string alias)
{
    std::string target = alias;

    if (! pkgdata->is_known_target (alias)) {
        const std::vector<std::string> & targets = pkgdata->get_targets ();
        for (unsigned int n = 0; n < targets.size (); n++) {
            const std::vector<std::string> & aliases = pkgdata->get_target_aliases (targets [n]);
            if (aliases.end () != std::find (aliases.begin (), aliases.end (), alias)) {
                target = targets [n];
                break;
            }
        }
    }
    return target;
}
