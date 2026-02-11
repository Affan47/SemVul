mud_profile_set_colors (MudProfile *profile, gint nr, guint r, guint g, guint b)
{
    GdkColor color[C_MAX];
    gchar *s;
    gint i;
    const gchar *key = mud_profile_gconf_get_key(profile, "ui/palette");

    RETURN_IF_NOTIFYING(profile);

    for (i = 0; i < C_MAX; i++)
    {
        if (i == nr)
        {
            color[i].red = r;
            color[i].green = g;
            color[i].blue = b;
        }
        else
        {
            color[i].red = profile->priv->preferences.Colors[i].red;
            color[i].green = profile->priv->preferences.Colors[i].green;
            color[i].blue = profile->priv->preferences.Colors[i].blue;
        }
    }

    s = gtk_color_selection_palette_to_string(color, C_MAX);
    gconf_client_set_string(profile->priv->gconf_client, key, s, NULL);
}
