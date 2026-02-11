release_re_str(struct re_str *str) {
    if (str == NULL)
        return;
    FREE(str->rx);
    str->len = 0;
}
