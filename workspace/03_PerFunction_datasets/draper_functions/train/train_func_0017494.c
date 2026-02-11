AWT_show_remark_branch(AW_device *device, const char *remark_branch, bool is_leaf, AW_pos x, AW_pos y, AW_pos alignment, AW_bitset filteri, AW_CL cd1, AW_CL cd2) {

    char       *end          = 0;
    int         bootstrap    = int(strtol(remark_branch, &end, 10));
    bool        is_bootstrap = end[0] == '%' && end[1] == 0;
    bool        show         = true;
    const char *text         = 0;

    if (is_bootstrap) {
        if (bootstrap == 100) {
            show           = !is_leaf;
            if (show) text = "100%";
        }
        else {
            if (bootstrap == 0) {
                text = "<1%";
            }
            else {
                text = GBS_global_string("%i%%", bootstrap);
            }
        }
    }
    else {
        text = remark_branch;
    }

    if (show) {
        awt_assert(text != 0);
        device->text(AWT_GC_BRANCH_REMARK, text, x, y, alignment, filteri, cd1, cd2);
    }

    return is_bootstrap && show;
}
