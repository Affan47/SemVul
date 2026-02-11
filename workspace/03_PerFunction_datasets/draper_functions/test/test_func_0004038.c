prepend_prefix(APP_VERSION* avp, char* in, char* out, int len) {
    if (strlen(avp->file_prefix)) {
        sprintf(out, "%s/%s", avp->file_prefix, in);
    } else {
        strlcpy(out, in, len);
    }
}
