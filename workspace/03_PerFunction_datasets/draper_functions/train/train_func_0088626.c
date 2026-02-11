get_valid_value_string(option_t *opt, const char *value)
{
    char *res;
    choice_t *choice;
    char **paramvalues;

    if (!value)
        return NULL;

    if (startswith(value, "From") && option_is_composite(find_option(&value[4])))
        return strdup(value);

    if (opt->type == TYPE_BOOL) {
        if (is_true_string(value))
            return strdup("1");
        else if (is_false_string(value))
            return strdup("0");
        else {
            _log("Could not interpret \"%s\" as boolean value for option \"%s\".\n", value, opt->name);
            return NULL;
        }
    }


    if ((strcmp(value, "Custom") != 0 || strcmp(opt->name, "PageSize") == 0) &&
	(choice = option_find_choice(opt, value)))
        return strdup(choice->value);

    if (opt->type == TYPE_ENUM) {
        if (!strcasecmp(value, "none"))
            return strdup("None");


        if (is_true_string(value)) {
            for (choice = opt->choicelist; choice; choice = choice->next) {
                if (is_true_string(choice->value))
                    return strdup(choice->value);
            }
        }
        else if (is_false_string(value)) {
            for (choice = opt->choicelist; choice; choice = choice->next) {
                if (is_false_string(choice->value))
                    return strdup(choice->value);
            }
        }
    }


    if (opt->paramlist) {
        paramvalues = paramvalues_from_string(opt, value);
        if (paramvalues) {
            res = paramvalues_to_string(opt, paramvalues);
            free(paramvalues);
            return (startswith(res, "Custom.") ? strdup(&res[7]) : strdup(res));
        }
    }
    else if (opt->foomatic_param)
        return get_valid_param_string(opt, opt->foomatic_param,
                              startswith(value, "Custom.") ? &value[7] : value);


    return NULL;
}
