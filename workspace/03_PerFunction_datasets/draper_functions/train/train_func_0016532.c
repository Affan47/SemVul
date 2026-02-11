jack_controller_deserialize_parameter_value(
    struct jack_controller *controller_ptr,
    const char * const * address,
    const char * option_value)
{
    const struct jack_parameter * param_ptr;
    union jackctl_parameter_value value;
    size_t size;

    param_ptr = jack_params_get_parameter(controller_ptr->params, address);
    if (param_ptr == NULL)
    {
        jack_error("Unknown parameter");
        goto ignore;
    }

    jack_info("setting parameter '%s':'%s':'%s' to value \"%s\"", address[0], address[1], address[2], option_value);

    switch (param_ptr->type)
    {
    case JackParamInt:
        value.i = atoi(option_value);
        break;
    case JackParamUInt:
        value.ui = strtoul(option_value, NULL, 10);
        break;
    case JackParamChar:
        if (option_value[0] == 0 || option_value[1] != 0)
        {
            jack_error("invalid char option value \"%s\"", option_value);
            goto ignore;
        }
        value.c = *option_value;
        break;
    case JackParamString:
        size = strlen(option_value);
        if (size >= sizeof(value.str))
        {
            jack_error("string option value \"%s\" is too long, max is %zu chars (including terminating zero)", option_value, sizeof(value.str));
            goto ignore;
        }

        strcpy(value.str, option_value);
        break;
    case JackParamBool:
        if (strcmp(option_value, "true") == 0)
        {
            value.b = true;
        }
        else if (strcmp(option_value, "false") == 0)
        {
            value.b = false;
        }
        else
        {
            jack_error("ignoring unknown bool value \"%s\"", option_value);
            goto ignore;
        }
        break;
    default:
        jack_error("Unknown type %d", (int)param_ptr->type);
        goto ignore;
    }

    if (param_ptr->vtable.set_value(param_ptr->obj, &value))
    {
        return;
    }

    jack_error("Parameter set failed");

ignore:
    jack_error("Ignoring restore attempt of parameter '%s':'%s':'%s'", address[0], address[1], address[2]);
}
