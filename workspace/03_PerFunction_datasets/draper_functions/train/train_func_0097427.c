_command_send(usb_handle *usb, const char *cmd,
                         const void *data, unsigned size,
                         char *response)
{
    int r;
    if (size == 0) {
        return -1;
    }

    r = _command_start(usb, cmd, size, response);
    if (r < 0) {
        return -1;
    }

    r = _command_data(usb, data, size);
    if (r < 0) {
        return -1;
    }

    r = _command_end(usb);
    if(r < 0) {
        return -1;
    }

    return size;
}
