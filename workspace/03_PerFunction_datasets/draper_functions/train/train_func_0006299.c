jack_controller_dbus_reserve_client_name(
    struct jack_dbus_method_call * call)
{
    int ret;
    const char * client_name;
    const char * client_uuid;

    if (!jack_dbus_get_method_args(
            call,
            DBUS_TYPE_STRING,
            &client_name,
            DBUS_TYPE_STRING,
            &client_uuid,
            DBUS_TYPE_INVALID))
    {

        return;
    }

    ret = jack_reserve_client_name(controller_ptr->client, client_name, client_uuid);
    if (ret < 0)
    {
        jack_dbus_error(call, JACK_DBUS_ERROR_GENERIC, "jack_reserve_client_name(name=\"%s\", uuid=\"%s\") failed (%d)", client_name, client_uuid, ret);
        return;
    }

    jack_dbus_construct_method_return_empty(call);
}
