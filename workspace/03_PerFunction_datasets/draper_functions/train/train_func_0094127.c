parse_string2(ZZJSON_CONFIG *config) {
    ZZJSON *zzjson = NULL;
    char *str;

    str = parse_string(config);
    if (str) {
        zzjson = config->calloc(1, sizeof(ZZJSON));
        if (!zzjson) {
            MEMERROR();
            config->free(str);
            return NULL;
        }
        zzjson->type = ZZJSON_STRING;
        zzjson->value.string.string = str;
    }
    return zzjson;
}
