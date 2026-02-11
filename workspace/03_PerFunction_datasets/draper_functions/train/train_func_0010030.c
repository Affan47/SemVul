fm_side_pane_set_show_hidden(FmSidePane *sp, gboolean show_hidden)
{
    GObjectClass *klass;
    GParamSpec *spec;

    if (sp->view == NULL)
        return FALSE;
    klass = G_OBJECT_GET_CLASS(sp->view);
    spec = g_object_class_find_property(klass, "show-hidden");
    if (spec == NULL || spec->value_type != G_TYPE_BOOLEAN)
        return FALSE;
    g_object_set(sp->view, "show-hidden", show_hidden, NULL);
    return TRUE;
}
