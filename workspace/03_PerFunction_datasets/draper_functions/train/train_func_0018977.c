broadcast_command_handler(struct ntb_connection *conn,
                          const uint8_t *data,
                          uint32_t command_length)
{
        struct ntb_connection_object_event event;
        ssize_t header_length;
        uint64_t broadcast_version;

        event.type = NTB_PROTO_INV_TYPE_BROADCAST;
        event.object_data_length = command_length;
        event.object_data = data;

        header_length = ntb_proto_get_command(data,
                                              command_length,

                                              NTB_PROTO_ARGUMENT_64,
                                              &event.nonce,

                                              NTB_PROTO_ARGUMENT_TIMESTAMP,
                                              &event.timestamp,

                                              NTB_PROTO_ARGUMENT_VAR_INT,
                                              &broadcast_version,

                                              NTB_PROTO_ARGUMENT_VAR_INT,
                                              &event.stream_number,

                                              NTB_PROTO_ARGUMENT_END);

        if (header_length == -1) {
                ntb_log("Invalid msg command received from %s",
                        conn->remote_address_string);
                set_error_state(conn);
                return false;
        }

        return emit_event(conn,
                          NTB_CONNECTION_EVENT_OBJECT,
                          &event.base);
}
