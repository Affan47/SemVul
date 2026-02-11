jack_controller_dbus_read_container(
    struct jack_dbus_method_call * call)
{
    const char * address[PARAM_ADDRESS_SIZE];
    dbus_bool_t leaf;
    DBusMessageIter iter;
    DBusMessageIter array_iter;


    if (!jack_controller_dbus_get_parameter_address(call, address))
    {


        return;
    }


    call->reply = dbus_message_new_method_return(call->message);
    if (!call->reply)
    {
        goto oom;
    }

    dbus_message_iter_init_append(call->reply, &iter);

    if (!jack_params_check_address(controller_ptr->params, address, false))
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

    leaf = jack_params_is_leaf_container(controller_ptr->params, address);
    if (!dbus_message_iter_append_basic(&iter, DBUS_TYPE_BOOLEAN, &leaf))
    {
        goto oom_unref;
    }

    if (!dbus_message_iter_open_container(&iter, DBUS_TYPE_ARRAY, "s", &array_iter))
    {
        goto oom_unref;
    }


    if (!jack_params_iterate_container(controller_ptr->params, address, append_node_name, &array_iter))
    {
        goto oom_close_unref;
    }

    dbus_message_iter_close_container(&iter, &array_iter);

    return;

oom_close_unref:
    dbus_message_iter_close_container(&iter, &array_iter);

oom_unref:
    dbus_message_unref(call->reply);
    call->reply = NULL;

oom:
    jack_error ("Ran out of memory trying to construct method return");
}
