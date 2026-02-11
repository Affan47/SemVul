gdm_normalize_language_name (const char *name)
{
        char *normalized_name;
        char *language_code;
        char *territory_code;
        char *codeset;
        char *modifier;

        if (name[0] == '\0') {
                return NULL;
        }

        gdm_parse_language_name (name,
                                 &language_code,
                                 &territory_code,
                                 &codeset, &modifier);

        normalized_name = construct_language_name (language_code,
                                                   territory_code,
                                                   codeset, modifier);
        g_free (language_code);
        g_free (territory_code);
        g_free (codeset);
        g_free (modifier);

        return normalized_name;
}
