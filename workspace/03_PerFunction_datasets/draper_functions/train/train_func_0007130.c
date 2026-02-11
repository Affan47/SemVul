dblayer_get_home_dir(struct ldbminfo *li, int *dbhome)
{
    dblayer_private *priv = (dblayer_private*)li->li_dblayer_private;
    char *home_dir = priv->dblayer_home_directory;
    if (dbhome)
        *dbhome = 0;

    if (priv->dblayer_dbhome_directory && *(priv->dblayer_dbhome_directory))
    {
        if (dbhome)
            *dbhome = 1;
        home_dir = priv->dblayer_dbhome_directory;
    }
    if (NULL == home_dir)
    {
        LDAPDebug(LDAP_DEBUG_ANY,"Db home directory is not set. "
            "Possibly %s (optionally %s) is missing in the config file.\n",
            CONFIG_DIRECTORY, CONFIG_DB_HOME_DIRECTORY, 0);
    }
    return home_dir;
}
