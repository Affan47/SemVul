write_loader_info (GString *contents, const char *path, GdkPixbufFormat *info)
{
        const GdkPixbufModulePattern *pattern;
        char **mime;
        char **ext;

        g_string_append_printf (contents, "\"%s\"\n", path);
        g_string_append_printf (contents, "\"%s\" %u \"%s\" \"%s\" \"%s\"\n",
                  info->name,
                  info->flags,
                  info->domain ? info->domain : GETTEXT_PACKAGE,
                  info->description,
                  info->license ? info->license : "");
        for (mime = info->mime_types; *mime; mime++) {
                g_string_append_printf (contents, "\"%s\" ", *mime);
        }
        g_string_append (contents, "\"\"\n");
        for (ext = info->extensions; *ext; ext++) {
                g_string_append_printf (contents, "\"%s\" ", *ext);
        }
        g_string_append (contents, "\"\"\n");
        for (pattern = info->signature; pattern->prefix; pattern++) {
                print_escaped (contents, pattern->prefix);
                print_escaped (contents, pattern->mask ? (const char *)pattern->mask : "");
                g_string_append_printf (contents, "%d\n", pattern->relevance);
        }
        g_string_append_c (contents, '\n');
}
