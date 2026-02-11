opal_dss_print_float(char **output, char *prefix,
                          float *src, opal_data_type_t type)
{
    char *prefx;


    if (NULL == prefix) asprintf(&prefx, " ");
    else prefx = prefix;


    if (NULL == src) {
        asprintf(output, "%sData type: OPAL_FLOAT\tValue: NULL pointer", prefx);
        return OPAL_SUCCESS;
    }

    asprintf(output, "%sData type: OPAL_FLOAT\tValue: %f", prefx, *src);

    return OPAL_SUCCESS;
}
