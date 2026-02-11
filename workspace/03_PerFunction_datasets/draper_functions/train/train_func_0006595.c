usb_read(usb_handle *h, void *_data, int len)
{
    unsigned char *data = (unsigned char*) _data;
    int n;

    D("++ usb_read ++\n");
    while(len > 0) {
        int xfer = (len > 4096) ? 4096 : len;

        D("[ usb read %d fd = %d], fname=%s\n", xfer, h->desc, h->fname);
        n = usb_bulk_read(h, data, xfer);
        D("[ usb read %d ] = %d, fname=%s\n", xfer, n, h->fname);
        if(n != xfer) {
            if((errno == ETIMEDOUT) && (h->desc != -1)) {
                D("[ timeout ]\n");
                if(n > 0){
                    data += n;
                    len -= n;
                }
                continue;
            }
            D("ERROR: n = %d, errno = %d (%s)\n",
                n, errno, strerror(errno));
            return -1;
        }

        len -= xfer;
        data += xfer;
    }

    D("-- usb_read --\n");
    return 0;
}
