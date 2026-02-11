findLoadConfigFile(struct cfoption *options, upath name) {
    upath configFile = YApplication::findConfigFile(name);
    bool rc = false;
    if (configFile != null) {
        YConfig::loadConfigFile(options, configFile);
        rc = true;
    }
    return rc;
}
