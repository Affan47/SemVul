object_find_by_flag(const object *who, int flag) {
    object *tmp;

    for (tmp = who->inv; tmp != NULL; tmp = tmp->below)
        if (QUERY_FLAG(tmp, flag))
            return tmp;

    return NULL;
}
