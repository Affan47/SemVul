menu_frame_select(ObMenuFrame *self, ObMenuEntryFrame *entry,
                       gboolean immediate)
{
    ObMenuEntryFrame *old = self->selected;
    ObMenuFrame *oldchild = self->child;
    ObMenuEntryFrame *oldchild_entry = self->child_entry;


    if (entry && entry->entry->type == OB_MENU_ENTRY_TYPE_SEPARATOR)
        entry = old;

    if (old == entry &&
        (!old || old->entry->type != OB_MENU_ENTRY_TYPE_SUBMENU))
        return;


    if (!entry && oldchild_entry)
        entry = oldchild_entry;

    if (config_submenu_show_delay) {

        if (submenu_show_timer) g_source_remove(submenu_show_timer);
        submenu_show_timer = 0;
    }

    self->selected = entry;

    if (old)
        menu_entry_frame_render(old);

    if (oldchild_entry) {

        if (oldchild_entry == self->selected) {


            remove_submenu_hide_timeout(oldchild);
        }
        else if (oldchild_entry == old) {


            if (immediate || config_submenu_hide_delay == 0)
                menu_frame_hide(oldchild);
            else if (config_submenu_hide_delay > 0) {
                if (submenu_hide_timer) g_source_remove(submenu_hide_timer);
                submenu_hide_timer =
                    g_timeout_add_full(G_PRIORITY_DEFAULT,
                                       config_submenu_hide_delay,
                                       submenu_hide_timeout, oldchild, NULL);
            }
        }
    }

    if (self->selected) {
        menu_entry_frame_render(self->selected);

        if (self->selected->entry->type == OB_MENU_ENTRY_TYPE_SUBMENU) {

            if (oldchild_entry != self->selected) {
                if (immediate || config_submenu_hide_delay == 0)
                    menu_entry_frame_show_submenu(self->selected);
                else if (config_submenu_hide_delay > 0) {
                    if (submenu_show_timer)
                        g_source_remove(submenu_show_timer);
                    submenu_show_timer =
                        g_timeout_add_full(G_PRIORITY_DEFAULT,
                                           config_submenu_show_delay,
                                           submenu_show_timeout,
                                           self->selected, NULL);
                }
            }


            else if (immediate && self->child && self->child->child) {
                menu_frame_hide(self->child->child);
                menu_frame_select(self->child, NULL, TRUE);
            }
        }
    }
}
