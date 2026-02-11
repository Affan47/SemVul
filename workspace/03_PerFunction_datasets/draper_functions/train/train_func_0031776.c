parse_hierarchy_key(section_config_t *section, char *value)
{
    int ret;

    ret = hierarchy_name_to_id(value);
    if (ML_UNDEFINED == ret) {
        return OMPI_ERROR;
    }

    section->config.topology_id = ret;

    return OMPI_SUCCESS;
}
