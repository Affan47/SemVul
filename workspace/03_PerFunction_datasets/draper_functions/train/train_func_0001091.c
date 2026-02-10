read_max_uid_value(FolderItem *item, guint * pmax_uid)
{
        gchar * path;
        gchar * file;
        FILE * f;
        guint max_uid;
        size_t r;

	path = folder_item_get_path(item);
	file = g_strconcat(path, G_DIR_SEPARATOR_S, MAX_UID_FILE, NULL);
	g_free(path);

        f = fopen(file, "r");
        g_free(file);
        if (f == NULL)
                return;
        r = fread(&max_uid, sizeof(max_uid), 1, f);
        if (r == 0) {
                fclose(f);
                return;
        }

        fclose(f);

        * pmax_uid = max_uid;
}
