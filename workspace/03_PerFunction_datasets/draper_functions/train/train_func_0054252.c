key_value_event_cb(enum ntb_key_value_event event,
                   int line_number,
                   const char *key,
                   const char *value,
                   void *user_data)
{
        struct ntb_load_outgoings_data *data = user_data;

        switch (event) {
        case NTB_KEY_VALUE_EVENT_HEADER:
                flush_outgoing(data);
                break;

        case NTB_KEY_VALUE_EVENT_PROPERTY:
                process_property(data, line_number, key, value);
                break;
        }
}
