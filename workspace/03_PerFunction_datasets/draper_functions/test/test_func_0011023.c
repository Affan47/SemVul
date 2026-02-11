opal_dss_compare_int16(int16_t *value1, int16_t *value2, opal_data_type_t type)
{
    if (*value1 > *value2) return OPAL_VALUE1_GREATER;

    if (*value2 > *value1) return OPAL_VALUE2_GREATER;

    return OPAL_EQUAL;
}
