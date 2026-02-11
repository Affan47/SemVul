rsvg_parse_style_attrs (RsvgHandle * ctx,
                        RsvgState * state,
                        const char *tag, const char *klazz, const char *id, RsvgPropertyBag * atts)
{
    int i = 0, j = 0;
    char *target = NULL;
    gboolean found = FALSE;
    GString *klazz_list = NULL;

    if (rsvg_property_bag_size (atts) > 0)
        rsvg_parse_style_pairs (ctx, state, atts);


    rsvg_lookup_apply_css_style (ctx, "*", state);


    if (tag != NULL) {
        rsvg_lookup_apply_css_style (ctx, tag, state);
    }

    if (klazz != NULL) {
        i = strlen (klazz);
        while (j < i) {
            found = FALSE;
            klazz_list = g_string_new (".");

            while (j < i && g_ascii_isspace (klazz[j]))
                j++;

            while (j < i && !g_ascii_isspace (klazz[j]))
                g_string_append_c (klazz_list, klazz[j++]);


            if (tag != NULL && klazz_list->len != 1 && id != NULL) {
                target = g_strdup_printf ("%s%s#%s", tag, klazz_list->str, id);
                found = found || rsvg_lookup_apply_css_style (ctx, target, state);
                g_free (target);
            }


            if (klazz_list->len != 1 && id != NULL) {
                target = g_strdup_printf ("%s#%s", klazz_list->str, id);
                found = found || rsvg_lookup_apply_css_style (ctx, target, state);
                g_free (target);
            }


            if (tag != NULL && klazz_list->len != 1) {
                target = g_strdup_printf ("%s%s", tag, klazz_list->str);
                found = found || rsvg_lookup_apply_css_style (ctx, target, state);
                g_free (target);
            }


            if (!found) {
                found = found || rsvg_lookup_apply_css_style (ctx, klazz_list->str, state);
            }
            g_string_free (klazz_list, TRUE);
        }
    }


    if (id != NULL) {
        target = g_strdup_printf ("#%s", id);
        rsvg_lookup_apply_css_style (ctx, target, state);
        g_free (target);
    }


    if (tag != NULL && id != NULL) {
        target = g_strdup_printf ("%s#%s", tag, id);
        rsvg_lookup_apply_css_style (ctx, target, state);
        g_free (target);
    }

    if (rsvg_property_bag_size (atts) > 0) {
        const char *value;

        if ((value = rsvg_property_bag_lookup (atts, "style")) != NULL)
            rsvg_parse_style (ctx, state, value);
        if ((value = rsvg_property_bag_lookup (atts, "transform")) != NULL)
            rsvg_parse_transform_attr (ctx, state, value);
    }
}
