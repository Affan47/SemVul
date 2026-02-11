_get_sfnt_info(FontInfo *fontinfo, const FT_Face face)
{
    gint    index,
            namecount = FT_Get_Sfnt_Name_Count(face);
    gchar   *version = NULL,
            *copyright = NULL,
            *description = NULL,
            *license = NULL,
            *license_url = NULL,
            *foundry = NULL;

    for (index=0; index < namecount; index++)
    {
        FT_SfntName sname;

        if (FT_Get_Sfnt_Name(face, index, &sname) != 0)
            continue;


        if (!(sname.platform_id == TT_PLATFORM_MICROSOFT &&
                sname.encoding_id == TT_MS_ID_UNICODE_CS &&
                sname.language_id == TT_MS_LANGID_ENGLISH_UNITED_STATES))
            continue;

        switch (sname.name_id)
        {
            case TT_NAME_ID_COPYRIGHT:
                g_free_and_nullify(copyright);
                copyright = G_CONVERT_8_2_16BE(sname);
                break;
            case TT_NAME_ID_VERSION_STRING:
                g_free_and_nullify(version);
                version = G_CONVERT_8_2_16BE(sname);
                break;
            case TT_NAME_ID_DESCRIPTION:
                g_free_and_nullify(description);
                description = G_CONVERT_8_2_16BE(sname);
                break;
            case TT_NAME_ID_LICENSE:
                g_free_and_nullify(license);
                license = G_CONVERT_8_2_16BE(sname);
                break;
            case TT_NAME_ID_LICENSE_URL:
                g_free_and_nullify(license_url);
                license_url = G_CONVERT_8_2_16BE(sname);
                break;
            case TT_NAME_ID_MANUFACTURER:
                g_free_and_nullify(foundry);
                foundry = G_CONVERT_8_2_16BE(sname);
                break;
            default:
                break;
        }
    }

    ADD_SFNT_PROP(fontinfo->version, version);
    ADD_SFNT_PROP(fontinfo->copyright, copyright);
    ADD_SFNT_PROP(fontinfo->description, description);
    ADD_SFNT_PROP(fontinfo->license, license);
    ADD_SFNT_PROP(fontinfo->license_url, license_url);

    if (foundry)
    {
        if(g_strcmp0(foundry, "Unknown") == 0)
            _get_foundry_from_notice(foundry, fontinfo);

        if (g_strcmp0(fontinfo->foundry, "Unknown") == 0
                            && (int) strlen(foundry) < 50)
        {
            g_free_and_nullify(fontinfo->foundry);
            fontinfo->foundry = g_strstrip(g_strdup(foundry));
        }

        g_free_and_nullify(foundry);
    }
}
