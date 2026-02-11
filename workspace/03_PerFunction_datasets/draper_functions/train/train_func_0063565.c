bus_dispatch_data_new (GDBusMessage  *message,
                       BusConnection *skip_connection)
{
    BusDispatchData *data = g_slice_new (BusDispatchData);

    data->message = (GDBusMessage *) g_object_ref (message);
    if (skip_connection) {
        data->skip_connection = (BusConnection *) g_object_ref (skip_connection);
    }
    else {
        data->skip_connection = NULL;
    }
    return data;
}
