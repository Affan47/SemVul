orte_util_convert_sysinfo_to_string(char **sysinfo_string,
					const char *cpu_type, const char *cpu_model)
{
    char *tmp;


    if (NULL == cpu_type) {
        asprintf(&tmp, "%s", ORTE_SCHEMA_INVALID_STRING);
    } else {
        asprintf(&tmp, "%s", cpu_type);
    }

    if (NULL == cpu_model) {
        asprintf(sysinfo_string, "%s%c%s", tmp, ORTE_SCHEMA_DELIMITER_CHAR, ORTE_SCHEMA_INVALID_STRING);
    } else {
        asprintf(sysinfo_string, "%s%c%s", tmp, ORTE_SCHEMA_DELIMITER_CHAR, cpu_model);
    }
    free(tmp);
    return ORTE_SUCCESS;
}
