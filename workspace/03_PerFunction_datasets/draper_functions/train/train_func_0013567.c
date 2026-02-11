jack_controller_dbus_get_client_name_by_uuid(
    struct jack_dbus_method_call * call)
{
    const char * client_uuid;
    char * client_name;

    if (!jack_dbus_get_method_args(
            call,
            DBUS_TYPE_STRING,
            &client_uuid,
            DBUS_TYPE_INVALID))
    {

        return;
    }

    client_name = jack_get_client_name_by_uuid(controller_ptr->client, client_uuid);
    if (client_name == NULL)
    {
        jack_dbus_error(call, JACK_DBUS_ERROR_GENERIC, "jack_get_client_name_by_uuid(\"%s\") failed", client_uuid);
        return;
    }

    jack_dbus_construct_method_return_single(call, DBUS_TYPE_STRING, (message_arg_t)(const char *)client_name);
    free(client_name);
}
