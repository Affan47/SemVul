read_file_info(const guchar *buffer, gsize size,
               FileInfo *info,
               GError **error)
{
    guint expected_size, i;
    const guchar *p;

    gwy_clear(info, 1);
    p = buffer + MAGIC_SIZE;

    for (i = 0; i < (HEADER_SIZE - MAGIC_SIZE)/8; i++) {
        gchar key[5];
        guint32 value;

        key[4] = '\0';
        memcpy(key, p, 4);
        p += 4;
        value = gwy_get_guint32_le(&p);
        if (!key[0])
            continue;

        gwy_debug("%s: 0x%04x", key, value);


        if (!value || value >= size)
            continue;

        else if (gwy_strequal(key, "DESC"))
            info->desc_offset = value;
        else if (gwy_strequal(key, "DATE"))
            info->date_offset = value;
        else if (gwy_strequal(key, "PLET"))
            info->palette_offset = value;
        else if (gwy_strequal(key, "IMAG"))
            info->image_offset = value;
        else if (gwy_strequal(key, "HARD"))
            info->hard_offset = value;
        else if (gwy_strequal(key, "IMGP"))
            info->img_p_offset = value;
        else if (gwy_strequal(key, "SDES"))
            info->short_desc_offset = value;
        else if (gwy_strequal(key, "KEYS"))
            info->keys_offset = value;
        else {
            gwy_debug("Unknown field %s", key);
        }
    }


    if (!(p = get_param_pointer(buffer, size,
                                info->image_offset, sizeof(guint16),
                                "IMAG", error)))
        return FALSE;
    info->img_res = gwy_get_guint16_le(&p);
    if (err_DIMENSION(error, info->img_res))
        return FALSE;


    info->image_data = (const guint16*)p;
    expected_size = (p - buffer) + info->img_res*info->img_res*sizeof(guint16);
    if (err_SIZE_MISMATCH(error, expected_size, size, FALSE))
        return FALSE;


    if (!(p = get_param_pointer(buffer, size,
                                info->hard_offset, sizeof(gfloat),
                                "HARD", error)))
        return FALSE;
    info->real_size = gwy_get_gfloat_le(&p);
    if (!((info->real_size = fabs(info->real_size)) > 0)) {
        g_warning("Real size is 0.0, fixing to 1.0");
        info->real_size = 1.0;
    }


    if (!(p = get_param_pointer(buffer, size,
                                info->img_p_offset + 8, sizeof(gfloat),
                                "IMGP", error)))
        return FALSE;
    info->z_scale = gwy_get_gfloat_le(&p);

    return TRUE;
}
