jack_dbus_construct_method_return_parameter(
    struct jack_dbus_method_call * call,
    dbus_bool_t is_set,
    int type,
    const char *signature,
    message_arg_t default_value,
    message_arg_t value)
{
    DBusMessageIter iter;


    call->reply = dbus_message_new_method_return (call->message);
    if (!call->reply)
    {
        goto fail;
    }

    dbus_message_iter_init_append (call->reply, &iter);


    if (!dbus_message_iter_append_basic (&iter, DBUS_TYPE_BOOLEAN, (const void *) &is_set))
    {
        goto fail_unref;
    }


    if (!jack_dbus_message_append_variant(&iter, type, signature, &default_value))
    {
        goto fail_unref;
    }
    if (!jack_dbus_message_append_variant(&iter, type, signature, &value))
    {
        goto fail_unref;
    }

    return;

fail_unref:
    dbus_message_unref (call->reply);
    call->reply = NULL;

fail:
    jack_error ("Ran out of memory trying to construct method return");
}
