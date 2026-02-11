fm_cell_renderer_pixbuf_dispose(GObject *object)
{
    FmCellRendererPixbuf *self;

    g_return_if_fail(object != NULL);
    g_return_if_fail(FM_IS_CELL_RENDERER_PIXBUF(object));

    self = FM_CELL_RENDERER_PIXBUF(object);
    if( self->fi )
    {
        fm_file_info_unref(self->fi);
        self->fi = NULL;
    }
    if(self->icon)
    {
        g_object_unref(self->icon);
        self->icon = NULL;
    }

    G_OBJECT_CLASS(fm_cell_renderer_pixbuf_parent_class)->dispose(object);
}
