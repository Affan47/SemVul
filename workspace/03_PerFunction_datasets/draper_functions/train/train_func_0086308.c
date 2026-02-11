make_re(enum re_type type) {
    struct re *re;
    if (make_ref(re) == 0)
        re->type = type;
    return re;
}
