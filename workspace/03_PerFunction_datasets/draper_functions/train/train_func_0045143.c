translateSpecialNumber(const scpi_special_number_def_t * specs, const char * str, size_t len, scpi_number_t * value) {
    int i;

    value->value = 0.0;
    value->unit = SCPI_UNIT_NONE;
    value->type = SCPI_NUM_NUMBER;

    if (specs == NULL) {
        return FALSE;
    }

    for (i = 0; specs[i].name != NULL; i++) {
        if (matchPattern(specs[i].name, strlen(specs[i].name), str, len)) {
            value->type = specs[i].type;
            return TRUE;
        }
    }

    return FALSE;
}
