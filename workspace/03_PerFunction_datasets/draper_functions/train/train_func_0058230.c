client_bring_windows_recursive(ObClient *self,
                                           guint desktop,
                                           gboolean helpers,
                                           gboolean modals,
                                           gboolean iconic)
{
    GSList *it;

    for (it = self->transients; it; it = g_slist_next(it))
        client_bring_windows_recursive(it->data, desktop,
                                       helpers, modals, iconic);

    if (((helpers && client_helper(self)) ||
         (modals && self->modal)) &&
        (!screen_compare_desktops(self->desktop, desktop) ||
         (iconic && self->iconic)))
    {
        if (iconic && self->iconic)
            client_iconify(self, FALSE, TRUE, FALSE);
        else
            client_set_desktop(self, desktop, FALSE, FALSE);
    }
}
