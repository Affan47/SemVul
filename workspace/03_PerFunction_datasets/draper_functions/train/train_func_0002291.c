orte_info_show_mca_group_params(const mca_base_var_group_t *group, bool want_internal)
{
    const mca_base_var_t *var;
    const int *variables;
    int ret, i, j, count;
    const int *groups;
    char **strings;

    variables = OPAL_VALUE_ARRAY_GET_BASE(&group->group_vars, const int);
    count = opal_value_array_get_size((opal_value_array_t *)&group->group_vars);

    for (i = 0 ; i < count ; ++i) {
        ret = mca_base_var_get(variables[i], &var);
        if (OPAL_SUCCESS != ret || ((var->mbv_flags & MCA_BASE_VAR_FLAG_INTERNAL) &&
                                    !want_internal)) {
            continue;
        }

        ret = mca_base_var_dump(variables[i], &strings, !orte_info_pretty ? MCA_BASE_VAR_DUMP_PARSABLE : MCA_BASE_VAR_DUMP_READABLE);
        if (OPAL_SUCCESS != ret) {
            continue;
        }

        for (j = 0 ; strings[j] ; ++j) {
            if (0 == j && orte_info_pretty) {
                char *message;

                asprintf (&message, "MCA %s", group->group_framework);
                orte_info_out(message, message, strings[j]);
                free(message);
            } else {
                orte_info_out("", "", strings[j]);
            }
            free(strings[j]);
        }
        free(strings);
    }

    groups = OPAL_VALUE_ARRAY_GET_BASE(&group->group_subgroups, const int);
    count = opal_value_array_get_size((opal_value_array_t *)&group->group_subgroups);

    for (i = 0 ; i < count ; ++i) {
        ret = mca_base_var_group_get(groups[i], &group);
        if (OPAL_SUCCESS != ret) {
            continue;
        }
        orte_info_show_mca_group_params(group, want_internal);
    }
}
