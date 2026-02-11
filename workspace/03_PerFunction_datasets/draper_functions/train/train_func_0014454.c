g_variant_get_image (GVariant *value)
{
    const gchar *strvalue = NULL;
    gsize length = 0;
    guchar *icondata;
    GdkPixbuf *img;

    if (g_variant_is_of_type (value, G_VARIANT_TYPE_STRING))
        strvalue = g_variant_get_string(value, NULL);

    if (!strvalue || !*strvalue) {
        g_warning ("%s: value does not contain a base64 encoded image",
                   __func__);
        return NULL;
    }

    icondata = g_base64_decode(strvalue, &length);
    img = gdk_pixbuf_new_from_encoded_data (icondata, length);

    g_free(icondata);
    return img;
}
