usb_write(usb_handle *h, const void *_data, int len)
{
    unsigned char *data = (unsigned char*) _data;
    int n;
    int need_zero = 0;

    if(h->zero_mask) {


        if(!(len & h->zero_mask)) {
            need_zero = 1;
        }
    }

    while(len > 0) {
        int xfer = (len > 4096) ? 4096 : len;

        n = usb_bulk_write(h, data, xfer);
        if(n != xfer) {
            D("ERROR: n = %d, errno = %d (%s)\n",
                n, errno, strerror(errno));
            return -1;
        }

        len -= xfer;
        data += xfer;
    }

    if(need_zero){
        n = usb_bulk_write(h, _data, 0);
        return n;
    }

    return 0;
}
