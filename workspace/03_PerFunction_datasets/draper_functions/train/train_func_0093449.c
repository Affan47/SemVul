lns_format_subtree_atype(struct lens *l, char **buf) {
    char *k = NULL, *v = NULL;
    const struct regexp *ktype = l->child->ktype;
    const struct regexp *vtype = l->child->vtype;
    int r, result = -1;

    if (ktype != NULL) {
        k = regexp_escape(ktype);
        if (k == NULL)
            goto done;
    }
    if (vtype != NULL) {
        v = regexp_escape(vtype);
        if (v == NULL)
            goto done;
        if (k == NULL)
            r = xasprintf(buf, "{ = /%s/ }", k, v);
        else
            r = xasprintf(buf, "{ /%s/ = /%s/ }", k, v);
    } else {
        if (k == NULL)
            r = xasprintf(buf, "{ }", k);
        else
            r = xasprintf(buf, "{ /%s/ }", k);
    }
    if (r < 0)
        goto done;

    result = 0;
 done:
    FREE(v);
    FREE(k);
    return result;
}
