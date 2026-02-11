lcrt_config_open(struct lcrt_config *config)
{
    if (config == NULL || strlen(config->db_name) == 0)
        return EINVAL;

    if (config->db != NULL)
        return LCRTE_OK;

    debug_where();
    config->db_rv = sqlite3_open(config->db_name, &config->db);
    if (config->db_rv != SQLITE_OK) {
        debug_print("Can't open database: %s\n", sqlite3_errmsg(config->db));
        sqlite3_close(config->db);
        config->db = NULL;
        return EIO;
    }
    return LCRTE_OK;
}
