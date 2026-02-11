jack_controller_dbus_set_parameter_value(
    struct jack_dbus_method_call * call)
{
    const char * address[PARAM_ADDRESS_SIZE];
    const struct jack_parameter * param_ptr;
    DBusMessageIter iter;
    DBusMessageIter variant_iter;
    message_arg_t arg;
    int arg_type;
    union jackctl_parameter_value value;


    if (!jack_controller_dbus_get_parameter_address_ex(call, &iter, address))
    {


        return;
    }


    param_ptr = jack_params_get_parameter(controller_ptr->params, address);
    if (param_ptr == NULL)
    {
        jack_dbus_error(
            call,
            JACK_DBUS_ERROR_INVALID_ARGS,
            "Invalid container address '%s':'%s':'%s' supplied to method '%s'.",
            address[0],
            address[1],
            address[2],
            call->method_name);
        return;
    }

    dbus_message_iter_next(&iter);

    if (dbus_message_iter_has_next(&iter))
    {
        jack_dbus_error(
            call,
            JACK_DBUS_ERROR_INVALID_ARGS,
            "Invalid arguments to method '%s'. Too many arguments.",
            call->method_name);
        return;
    }

    if (dbus_message_iter_get_arg_type(&iter) != DBUS_TYPE_VARIANT)
    {
        jack_dbus_error(
            call,
            JACK_DBUS_ERROR_INVALID_ARGS,
            "Invalid arguments to method '%s'. Value to set must be variant.",
            call->method_name);
        return;
    }

    dbus_message_iter_recurse (&iter, &variant_iter);
    dbus_message_iter_get_basic(&variant_iter, &arg);
    arg_type = dbus_message_iter_get_arg_type(&variant_iter);


    if (PARAM_TYPE_JACK_TO_DBUS(param_ptr->type) != arg_type)
    {
        jack_dbus_error(
            call,
            JACK_DBUS_ERROR_INVALID_ARGS,
            "Parameter value type mismatch: was expecting '%c', got '%c'",
            (char)PARAM_TYPE_JACK_TO_DBUS(param_ptr->type),
            (char)arg_type);
        return;
    }

    if (!jack_controller_dbus_to_jack_variant(
            arg_type,
            &arg,
            &value))
    {
        jack_dbus_error(
            call,
            JACK_DBUS_ERROR_INVALID_ARGS,
            "Cannot convert parameter value");
        return;
    }

    param_ptr->vtable.set_value(param_ptr->obj, &value);

    jack_controller_pending_save(controller_ptr);

    jack_dbus_construct_method_return_empty(call);

}
