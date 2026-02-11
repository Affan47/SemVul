ldp_print(register const u_char *pptr, register u_int len) {

    int processed;
    while (len > (sizeof(struct ldp_common_header) + sizeof(struct ldp_msg_header))) {
        processed = ldp_msg_print(pptr);
        if (processed == 0)
            return;
        len -= processed;
        pptr += processed;
    }
}
