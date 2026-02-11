object_find_by_type_and_arch_name(const object *who, int type, const char *name) {
    object *tmp;

    for (tmp = who->inv; tmp != NULL; tmp = tmp->below)
        if (tmp->type == type && strcmp(tmp->arch->name, name) == 0)
            return tmp;

    return NULL;
}
