aug_match(const struct augeas *aug, const char *pathin, char ***matches) {
    struct pathx *p = NULL;
    struct tree *tree;
    int cnt = 0;

    api_entry(aug);

    if (matches != NULL)
        *matches = NULL;

    if (STREQ(pathin, "/")) {
        pathin = "/*";
    }

    p = pathx_aug_parse(aug, aug->origin, tree_root_ctx(aug), pathin, true);
    ERR_BAIL(aug);

    for (tree = pathx_first(p); tree != NULL; tree = pathx_next(p)) {
        if (! TREE_HIDDEN(tree))
            cnt += 1;
    }
    ERR_BAIL(aug);

    if (matches == NULL)
        goto done;

    if (ALLOC_N(*matches, cnt) < 0)
        goto error;

    int i = 0;
    for (tree = pathx_first(p); tree != NULL; tree = pathx_next(p)) {
        if (TREE_HIDDEN(tree))
            continue;
        (*matches)[i] = path_of_tree(tree);
        if ((*matches)[i] == NULL) {
            goto error;
        }
        i += 1;
    }
    ERR_BAIL(aug);
 done:
    free_pathx(p);
    api_exit(aug);
    return cnt;

 error:
    if (matches != NULL) {
        if (*matches != NULL) {
            for (i=0; i < cnt; i++)
                free((*matches)[i]);
            free(*matches);
        }
    }
    free_pathx(p);
    api_exit(aug);
    return -1;
}
