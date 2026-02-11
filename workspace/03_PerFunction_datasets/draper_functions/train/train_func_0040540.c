fm_places_view_finalize(GObject *object)
{
    FmPlacesView* self;

    g_return_if_fail(object != NULL);
    g_return_if_fail(FM_IS_PLACES_VIEW(object));
    self = (FmPlacesView*)object;

    if(self->clicked_row)
        gtk_tree_path_free(self->clicked_row);

    G_OBJECT_CLASS(fm_places_view_parent_class)->finalize(object);
}
