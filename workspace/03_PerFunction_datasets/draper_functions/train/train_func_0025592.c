menu_frame_free(ObMenuFrame *self)
{
    if (self) {
        while (self->entries) {
            menu_entry_frame_free(self->entries->data);
            self->entries = g_list_delete_link(self->entries, self->entries);
        }

        stacking_remove(MENUFRAME_AS_WINDOW(self));
        window_remove(self->window);

        RrAppearanceFree(self->a_items);

        XDestroyWindow(obt_display, self->window);

        g_slice_free(ObMenuFrame, self);
    }
}
