fb_download_data_sparse_write(void *priv, const void *data, int len)
{
    int r;
    usb_handle *usb = priv;
    int to_write;
    const char *ptr = data;

    if (usb_buf_len) {
        to_write = min(USB_BUF_SIZE - usb_buf_len, len);

        memcpy(usb_buf + usb_buf_len, ptr, to_write);
        usb_buf_len += to_write;
        ptr += to_write;
        len -= to_write;
    }

    if (usb_buf_len == USB_BUF_SIZE) {
        r = _command_data(usb, usb_buf, USB_BUF_SIZE);
        if (r != USB_BUF_SIZE) {
            return -1;
        }
        usb_buf_len = 0;
    }

    if (len > USB_BUF_SIZE) {
        if (usb_buf_len > 0) {
            sprintf(ERROR, "internal error: usb_buf not empty\n");
            return -1;
        }
        to_write = round_down(len, USB_BUF_SIZE);
        r = _command_data(usb, ptr, to_write);
        if (r != to_write) {
            return -1;
        }
        ptr += to_write;
        len -= to_write;
    }

    if (len > 0) {
        if (len > USB_BUF_SIZE) {
            sprintf(ERROR, "internal error: too much left for usb_buf\n");
            return -1;
        }
        memcpy(usb_buf, ptr, len);
        usb_buf_len = len;
    }

    return 0;
}
