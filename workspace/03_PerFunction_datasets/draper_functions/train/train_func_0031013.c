free_arch(archetype *at) {
    if (at->name)
        free_string(at->name);
    if (at->clone.name)
        free_string(at->clone.name);
    if (at->clone.name_pl)
        free_string(at->clone.name_pl);
    if (at->clone.title)
        free_string(at->clone.title);
    if (at->clone.race)
        free_string(at->clone.race);
    if (at->clone.slaying)
        free_string(at->clone.slaying);
    if (at->clone.msg)
        free_string(at->clone.msg);
    free(at->clone.discrete_damage);
    object_free_key_values(&at->clone);
    free(at);
}
