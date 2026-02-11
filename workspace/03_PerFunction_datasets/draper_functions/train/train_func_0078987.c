globus_gram_job_manager_rsl_attribute_get_string_value(
    globus_rsl_t *                      rsl,
    const char *                        attribute,
    const char **                       value_ptr)
{
    globus_list_t *                     attributes;
    globus_list_t *                     node;
    int                                 rc = GLOBUS_SUCCESS;

    attributes = globus_rsl_boolean_get_operand_list(rsl);

    node = globus_list_search_pred(
            attributes,
            globus_l_gram_job_manager_rsl_match,
            (void *) attribute);
    if (node == NULL)
    {
        rc = GLOBUS_GRAM_PROTOCOL_ERROR_UNDEFINED_ATTRIBUTE;

        goto search_failed;
    }
    *value_ptr = globus_rsl_value_literal_get_string(
            globus_rsl_relation_get_single_value(
                    globus_list_first(node)));

search_failed:
    if (rc != GLOBUS_SUCCESS)
    {
        *value_ptr = NULL;
    }
    return rc;
}
