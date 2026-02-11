test38_aux_bNopen (struct emuFile * f, bstring b) {
    if (NULL == f || NULL == b) return -__LINE__;
    f->ofs = 0;
    f->contents = b;
    return 0;
}
