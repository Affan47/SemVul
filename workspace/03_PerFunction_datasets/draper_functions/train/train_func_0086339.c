fs_ml_init_2() {
    fs_ml_video_mode mode;
    memset(&mode, 0, sizeof(fs_ml_video_mode));
    if (fs_ml_video_mode_get_current(&mode) == 0) {
        g_fs_ml_target_refresh_rate = mode.fps;
    }
    else {
        fs_log("WARNING: could not read refresh rate from current mode\n");
        g_fs_ml_target_refresh_rate = 0;
    }
    if (g_fs_ml_target_refresh_rate) {
        g_fs_ml_target_frame_time = 1000000 / g_fs_ml_target_refresh_rate;
    }
    fs_log("assuming refresh rate: %d (%d usec per frame)\n",
            g_fs_ml_target_refresh_rate, g_fs_ml_target_frame_time);

    init_input();
    g_fs_ml_video_screenshot_mutex = fs_mutex_create();
}
