gl_font_util_validate_family (const gchar *family)
{
        const GList *installed_families;
        gchar       *good_family;

        installed_families = gl_font_util_get_all_families ();

        if (g_list_find_custom ((GList *)installed_families,
                                family,
                                (GCompareFunc)g_utf8_collate))
        {
                good_family = g_strdup (family);
        }
        else if (g_list_find_custom ((GList *)installed_families,
                                     "Sans",
                                     (GCompareFunc)g_utf8_collate))
        {
                good_family = g_strdup ("Sans");
        }
        else if (installed_families != NULL)
        {
                good_family = g_strdup (installed_families->data);
        }
        else
        {
                good_family = NULL;
        }

        return good_family;
}
