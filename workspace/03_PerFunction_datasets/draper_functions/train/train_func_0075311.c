options_config_get_enum(char *name, config_enumeration_type* enumeration, int *result) {
    int i;
    if(config_get_string(name)) {
        if(config_get_enum(name, enumeration, &i)) {
            *result = i;
            return 1;
        }
    }
    return 0;
}
