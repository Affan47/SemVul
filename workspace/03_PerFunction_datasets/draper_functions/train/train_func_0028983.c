GetBoolDefault(const char* name, bool def)
{
    ACE_TString val;
    if (!GetValueHelper(mConf, name, val))
        return def;

    const char* str = val.c_str();
    if (strcmp(str, "true") == 0 || strcmp(str, "TRUE") == 0 ||
            strcmp(str, "yes") == 0 || strcmp(str, "YES") == 0 ||
            strcmp(str, "1") == 0)
        return true;
    else
        return false;
}
