gnc_date_format_new_with_label (const char *label)
{
    GNCDateFormat *gdf;
    GNCDateFormatPriv *priv;

    gdf = g_object_new(GNC_TYPE_DATE_FORMAT, NULL);
    priv = GNC_DATE_FORMAT_GET_PRIVATE(gdf);

    if (label)
        gtk_label_set_text(GTK_LABEL(priv->label), label);

    gnc_date_format_compute_format(gdf);
    return GTK_WIDGET(gdf);
}
