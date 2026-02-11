cpl_mask_load_window(const char * filename,
                                cpl_size     pnum,
                                cpl_size     xtnum,
                                cpl_size     llx,
                                cpl_size     lly,
                                cpl_size     urx,
                                cpl_size     ury)
{

    cpl_mask * self = cpl_mask_load_one(filename, pnum, xtnum,
                                        CPL_TRUE, llx, lly, urx, ury);

    if (self == NULL) (void)cpl_error_set_where_();

    return self;

}
