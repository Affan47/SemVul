shadow_new(filter_t *f)
{
    shadow_t *shadow;

    g_assert(f != NULL);
    g_assert(f->name != NULL);

    if (GUI_PROPERTY(gui_debug) >= 6)
        g_debug("creating shadow for: %s", f->name);

    WALLOC0(shadow);
    shadow->filter   = f;
    shadow->current  = g_list_copy(f->ruleset);
    shadow->added    = NULL;
    shadow->removed  = NULL;
    shadow->refcount = f->refcount;
    shadow->flags    = f->flags;

    shadow_filters = g_list_append(shadow_filters, shadow);

    return shadow;
}
