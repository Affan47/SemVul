mud_tray_update_icon(MudTray *tray, enum mud_tray_status icon)
{
        const gchar *icon_name = NULL;

        switch (icon) {
                case offline:

			icon_name = "gnome-mud";
                        break;
                case offline_connecting:
                case online_connecting:
                        icon_name = "gnome-mud";
                        break;
                case online:

			icon_name = "gnome-mud";
                        break;
        }

        gtk_status_icon_set_from_icon_name(tray->priv->icon, icon_name);
}
