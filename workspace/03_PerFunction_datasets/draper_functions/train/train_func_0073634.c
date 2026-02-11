gst_vaapi_mini_object_new0(const GstVaapiMiniObjectClass *object_class)
{
    GstVaapiMiniObject *object;
    guint sub_size;

    object = gst_vaapi_mini_object_new(object_class);
    if (!object)
        return NULL;

    object_class = object->object_class;

    sub_size = object_class->size - sizeof(*object);
    if (sub_size > 0)
        memset(((guchar *)object) + sizeof(*object), 0, sub_size);
    return object;
}
