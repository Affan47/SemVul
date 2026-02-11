Config_load(const char *config_file, const char *db_file)
{
    int rc = 0;
    tst_t *settings = NULL;
    struct tagbstring SETTINGS_VAR = bsStatic("settings");
    struct tagbstring MIMETYPES_VAR = bsStatic("mimetypes");

    settings = Parse_config_file(config_file);
    check(settings != NULL, "Error parsing config file: %s.", config_file);

    rc = Config_setup(db_file);
    check(rc == 0, "Failed to configure config db: %s", db_file);

    rc = AST_walk(settings, Server_load);
    check(rc == 0, "Failed to process the config file: %s", config_file);

    Value *set = AST_get(settings, settings, &SETTINGS_VAR, VAL_HASH);

    if(set) {
        rc = AST_walk_hash(settings, set, Settings_load);
        check(rc == 0, "Failed to load the settings. Aborting.");
    }

    rc = Mimetypes_import();
    check(rc == 0, "Failed to import default mimetypes.");

    Value *mime = AST_get(settings, settings, &MIMETYPES_VAR, VAL_HASH);
    if(mime) {
        AST_walk_hash(settings, mime, Mimetypes_load);
        check(rc == 0, "Failed to load the mimetypes. Aborting.");
    }

    rc = Config_commit();
    check(rc == 0, "Failed to commit config db: %s", db_file);

    AST_destroy(settings);
    DB_close();
    return 0;
error:
    AST_destroy(settings);
    DB_close();
    return -1;
}
