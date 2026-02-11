config_params(struct config_group *group)
{
    struct vector *params;
    size_t size;

    params = vector_new();
    for (; group != NULL; group = group->parent) {
        size = hash_count(group->params);
        vector_resize(params, params->allocated + size);
        hash_traverse(group->params, parameter_collect, params);
    }
    return params;
}
