gppot_filter_show_inactive_toggled_cb (GtkToggleButton *button,
                                       OwnerFilterDialog *fd)
{
    g_return_if_fail(GTK_IS_TOGGLE_BUTTON(button));

    ENTER("button %p", button);
    fd->show_inactive = gtk_toggle_button_get_active(button);
    gnc_tree_view_owner_refilter(fd->tree_view);
    LEAVE("show_inactive %d", fd->show_inactive);
}
