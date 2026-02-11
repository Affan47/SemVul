ini_serialize_cb(const char *property,
                            int property_len,
                            int type,
                            void *data,
                            int length,
                            void *custom_data,
                            int *stop)
{
    int error = EOK;
    struct simplebuffer *sbobj;
    struct value_obj *vo;

    TRACE_FLOW_ENTRY();


    if(type == COL_TYPE_BINARY) {
        sbobj = (struct simplebuffer *)custom_data;
        vo = *((struct value_obj **)(data));
        error = value_serialize(vo, property, sbobj);
        if (error) {
            TRACE_ERROR_NUMBER("Failed to serizlize value", error);
            *stop = 1;
        }
    }

    TRACE_FLOW_EXIT();
    return error;
}
