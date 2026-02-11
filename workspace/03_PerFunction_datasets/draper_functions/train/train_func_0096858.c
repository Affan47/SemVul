viewkeyAwar(AW_root *aw_root,AW_default awdef,int i, const char *name, bool string_awar) {
    const char *awar_name = viewkeyAwarName(i, name);
    AW_awar    *awar      = 0;
    if (string_awar) awar = aw_root->awar_string(awar_name, "", awdef);
    else        awar      = aw_root->awar_int(awar_name, 0, awdef);
    return awar;
}
