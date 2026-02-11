discover_device_free(discover_device_t *devices, int free_data)
{
    discover_device_t *device, *last;

    last = NULL;

    for (device = devices;
         device;
         device = device->next) {
        if (device->busclass) {
            free(device->busclass);
        }

        if (device->model_id) {
            free(device->model_id);
        }

        if (device->model_name) {
            free(device->model_name);
        }

        if (device->vendor_id) {
            free(device->vendor_id);
        }

        if (device->vendor_name) {
            free(device->vendor_name);
        }

        if (free_data && device->data) {
            discover_data_free(device->data);
            free(device->data);
        }

        if (last) {
            free(last);
        }
        last = device;
    }

    if (last) {
        free(last);
    }
}
