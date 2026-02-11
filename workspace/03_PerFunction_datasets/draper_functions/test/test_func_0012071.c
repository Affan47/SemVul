on_resize(int width, int height) {
    if (width == g_fs_ml_video_width && height == g_fs_ml_video_height) {
        fs_log("got resize event, but size was unchanged\n");
        return;
    }
    if (g_fs_emu_video_fullscreen) {
        fs_log("not updating window size in fullscreen\n");
    }
    else if (width == g_fullscreen_width &&
        height == g_fullscreen_height) {
        fs_log("not setting window size to fullscreen size\n");
    }
    else {
        g_window_width = width;
        g_window_height = height;
        fs_log("resize event %d %d\n", width, height);
    }
#ifdef MACOSX
        destroy_opengl_state();
#endif
        set_video_mode();
#ifdef MACOSX
        recreate_opengl_state();
#endif
}
