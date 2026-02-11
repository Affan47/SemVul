filter_remove_rule(filter_t *f, rule_t *r)
{
    shadow_t *shadow;
    shadow_t *target_shadow;
    gboolean in_shadow_current;
    gboolean in_shadow_removed;
    gboolean in_filter;

    g_assert(f != NULL);
    g_assert(r != NULL);
    g_assert(r->target != NULL);

    shadow = shadow_find(f);
    target_shadow = shadow_find(r->target);

    in_filter = g_list_find(f->ruleset, r) != NULL;


    if (shadow != NULL) {
        in_shadow_current = g_list_find(shadow->current, r) != NULL;
        in_shadow_removed = g_list_find(shadow->removed, r) != NULL;
    } else {


        in_shadow_current = in_filter;
        in_shadow_removed = FALSE;
    }


    if (in_shadow_current && (shadow != NULL)) {
        shadow->current = g_list_remove(shadow->current, r);
        shadow->added = g_list_remove(shadow->added, r);
    }

    if (in_shadow_removed && (shadow != NULL))
       shadow->removed = g_list_remove(shadow->removed, r);

    if (in_filter)
        f->ruleset = g_list_remove(f->ruleset, r);


    if (in_filter) {
        r->target->refcount --;

        if (GUI_PROPERTY(gui_debug) >= 6)
            g_debug("decreased refcount on \"%s\" to %d",
                r->target->name, r->target->refcount);
    }

    if (in_shadow_current) {
        if (target_shadow != NULL) {
            target_shadow->refcount --;

            if (GUI_PROPERTY(gui_debug) >= 6)
                g_debug("decreased refcount on shadow of \"%s\" to %d",
                    target_shadow->filter->name, target_shadow->refcount);
        }
    }

    if (!in_filter && !in_shadow_current) {
        g_warning("rule unknown in context: aborting removal without freeing");
        return;
    }

    filter_free_rule(r);


     {
        GList *ruleset;

        ruleset = (shadow != NULL) ? shadow->current : f->ruleset;

        if (work_filter == f)
            filter_gui_set_ruleset(ruleset);
        filter_gui_update_rule_count(f, ruleset);
    }
}
