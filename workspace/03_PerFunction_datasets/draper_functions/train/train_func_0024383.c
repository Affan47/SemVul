bytearray_append_ba(bytearray_t *ba, bytearray_t *to_append) {
    if (to_append == NULL) {
        log_warn("Tried to append NULL bytearray\n");
        return -1;
    }

    return bytearray_append(ba, to_append->data, to_append->len);
}
