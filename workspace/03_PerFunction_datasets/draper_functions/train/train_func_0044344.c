awar_changed_cb(AW_root *, AW_CL cl_awt_mask_awar_item) {
    if (!in_awar_changed_callback) {
        in_awar_changed_callback   = true;
        awt_mask_awar_item *item = (awt_mask_awar_item*)cl_awt_mask_awar_item;
        awt_assert(item);
        if (item) item->awar_changed();
        in_awar_changed_callback   = false;
    }
}
