erase_db(kbconfig *config)
{
    for (int i=0; i < config->segments; i++) {
        if (!uses_segment(config, i)) continue;

        char *command = g_strdup_printf("rm -rf %s/%s/", FS_STORE_ROOT, config->name);
	system(command);
	g_free(command);
    }
    create_dir(config);
}
