rhkspm32_get_metadata(RHKPage *rhkpage)
{
    GwyContainer *meta;
    const gchar *s;

    meta = gwy_container_new();

    gwy_container_set_string_by_name(meta, "Tunneling voltage",
                                     g_strdup_printf("%g mV",
                                                     1e3*rhkpage->iv.offset));
    gwy_container_set_string_by_name(meta, "Current",
                                     g_strdup_printf("%g nA",
                                                     1e9*rhkpage->iv.scale));
    if (rhkpage->id)
        gwy_container_set_string_by_name(meta, "Id",
                                         g_strdup_printf("%u", rhkpage->id));
    if (rhkpage->date && *rhkpage->date)
        gwy_container_set_string_by_name(meta, "Date", g_strdup(rhkpage->date));
    if (rhkpage->comment && *rhkpage->comment)
        gwy_container_set_string_by_name(meta, "Comment",
                                         g_strdup(rhkpage->comment));
    if (rhkpage->label && *rhkpage->label)
        gwy_container_set_string_by_name(meta, "Label",
                                         g_strdup(rhkpage->label));

    s = gwy_enum_to_string(rhkpage->page_type,
                           scan_directions, G_N_ELEMENTS(scan_directions));
    if (s && *s)
        gwy_container_set_string_by_name(meta, "Image type", g_strdup(s));


    if (rhkpage->e_alpha)
        gwy_container_set_string_by_name(meta, "Angle",
                                         g_strdup_printf("%g deg",
                                                         rhkpage->alpha));

    return meta;
}
