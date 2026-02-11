lcrt_accels_init_local_config(struct lcrt_accels *laccels)
{
    char db_name[256];
    int i;
    int key[LCRT_KB_NUMBER][2] = {LCRT_KB_KEY};

    snprintf(db_name, sizeof(db_name), "%s/%s/", lcrt_config_get_local_dir(), LCRT_ACCELS_CONFIG_DIR);
    lcrt_fmkdir(db_name);
    strcat(db_name, LCRT_ACCELS_DB);
    lcrt_config_init(&laccels->config.ldb, db_name, LCRT_IACCELS_TABLE);

    for (i = 0; i < LCRT_KB_NUMBER; i++) {
        laccels->config.key[i][0] = key[i][0];
        laccels->config.key[i][1] = key[i][1];
        debug_print("name = [%-20s] value = [%-20s] shortcut = {%-5d, %d}\n",
                laccels->config.name[i],
                laccels->config.value[i],
                laccels->config.key[i][0],
                laccels->config.key[i][1]);
    }
    laccels->get_ldb = lcrt_accels_get_ldb_name;
    laccels->get_ltb = lcrt_accels_get_ltb_name;

    return 0;
}
