collect_locales_from_locale_file (const char *locale_file)
{
        FILE *langlist;
        char curline[256];
        char *getsret;

        if (locale_file == NULL)
                return;

        langlist = fopen (locale_file, "r");

        if (langlist == NULL)
                return;

        for (;;) {
                char *name;
                char *lang;
                char **lang_list;
                int i;

                getsret = fgets (curline, sizeof (curline), langlist);
                if (getsret == NULL)
                        break;

                if (curline[0] <= ' ' ||
                    curline[0] == '#')
                        continue;

                name = strtok (curline, " \t\r\n");
                if (name == NULL)
                        continue;

                lang = strtok (NULL, " \t\r\n");
                if (lang == NULL)
                        continue;

                lang_list = g_strsplit (lang, ",", -1);
                if (lang_list == NULL)
                        continue;

                lang = NULL;
                for (i = 0; lang_list[i] != NULL; i++) {
                        if (add_locale (lang_list[i], FALSE)) {
                                break;
                        }
                }
                g_strfreev (lang_list);
        }

        fclose (langlist);
}
