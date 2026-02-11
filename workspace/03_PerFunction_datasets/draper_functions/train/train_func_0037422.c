null_device_factory(char * device_name, char * device_type, char * device_node) {
    Device * device;
    g_assert(0 == strcmp(device_type, "null"));
    device = DEVICE(g_object_new(TYPE_NULL_DEVICE, NULL));
    device_open_device(device, device_name, device_type, device_node);
    return device;
}
