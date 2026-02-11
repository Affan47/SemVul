gwy_selection_duplicate_default(GObject *object)
{
    GwySelection *selection, *duplicate;
    guint object_size;

    g_return_val_if_fail(GWY_IS_SELECTION(object), NULL);
    selection = GWY_SELECTION(object);
    object_size = GWY_SELECTION_GET_CLASS(selection)->object_size;
    duplicate = g_object_new(G_TYPE_FROM_INSTANCE(object), NULL);
    g_array_set_size(duplicate->objects, 0);
    g_array_append_vals(duplicate->objects,
                        selection->objects->data, selection->n*object_size);
    duplicate->n = selection->n;
    g_array_set_size(duplicate->objects, selection->objects->len);

    return (GObject*)duplicate;
}
