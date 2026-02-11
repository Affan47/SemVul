client_writable(int fd, short event, void *arg) {
    int ret = evbuffer_write(out_buf, fd);
    if (ret < 0) {
        client_destroy(strerror(errno));
    } else if (ret == 0) {
        client_destroy("null write?");
    } else if (EVBUFFER_LENGTH(out_buf) > 0) {
        event_add(&wr_event, NULL);
    }
}
