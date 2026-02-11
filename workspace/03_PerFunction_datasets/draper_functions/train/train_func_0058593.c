aug_get(const struct augeas *aug, const char *path, const char **value) {
    struct pathx *p = NULL;
    struct tree *match;
    int r;

    api_entry(aug);

    p = pathx_aug_parse(aug, aug->origin, tree_root_ctx(aug), path, true);
    ERR_BAIL(aug);

    if (value != NULL)
        *value = NULL;

    r = pathx_find_one(p, &match);
    ERR_BAIL(aug);
    ERR_THROW(r > 1, aug, AUG_EMMATCH, "There are %d nodes matching %s",
              r, path);

    if (r == 1 && value != NULL)
        *value = match->value;
    free_pathx(p);

    api_exit(aug);
    return r;
 error:
    free_pathx(p);
    api_exit(aug);
    return -1;
}
