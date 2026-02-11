ED4_create_gc_window(AW_root *aw_root, AW_gc_manager id) {
    static AW_window *gc_win = 0;
    if (!gc_win) {
        gc_win = AW_create_gc_window(aw_root, id);
    }
    return gc_win;
}
