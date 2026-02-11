RegInit(const char* regname, const char* dirname)
{
    destroy_config();
    sConfigDir = dirname ? : DEFAULT_DIR;
    sConfigName = regname ? : DEFAULT_NAME;

    return get_config();
}
