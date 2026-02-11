globus_gram_job_manager_rsl_remove_attribute(
    globus_rsl_t *                      rsl,
    char *                              attribute)
{
    globus_list_t **                    operand_ref;
    globus_list_t *                     node;

    if(! globus_rsl_is_boolean_and(rsl))
    {
        return GLOBUS_GRAM_PROTOCOL_ERROR_BAD_RSL;
    }
    operand_ref = globus_rsl_boolean_get_operand_list_ref(rsl);
    node = globus_list_search_pred(*operand_ref,
                                   globus_l_gram_job_manager_rsl_match,
                                   attribute);
    if(node)
    {
        globus_rsl_free_recursive(globus_list_remove(operand_ref, node));
    }
    return GLOBUS_SUCCESS;
}
