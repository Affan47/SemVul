parse_fragmentation_key(section_config_t *section, char *value)
{
    if(!strcasecmp(value, "enable")) {
        section->config.fragmentation_enabled = 1;
    } else if (!strcasecmp(value, "disable")) {
        section->config.fragmentation_enabled = 0;
    } else {
        ML_ERROR(("Line %d, unexpected fragmentation value %s. Legal values are: enable/disable",
                    coll_ml_config_yynewlines, value));
        return OMPI_ERROR;
    }
    return OMPI_SUCCESS;
}
