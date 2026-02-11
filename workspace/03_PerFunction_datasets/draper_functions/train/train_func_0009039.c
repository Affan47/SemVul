xcf_write_fake_hierarchy(xcf_write_ctx *xc)
{
    int widthf = xc->width, heightf = xc->height;
    int i;

    for (i = 1; i < xc->n_levels; i++) {
        widthf >>= 1;
        heightf >>= 1;
        xcf_write_32(xc, widthf);
        xcf_write_32(xc, heightf);
        xcf_write_32(xc, 0);
    }
    return 0;
}
