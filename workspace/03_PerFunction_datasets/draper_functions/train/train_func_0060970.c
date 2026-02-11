handle_quit_sequence() {
    int fade_time = fs_config_get_int_clamped("fade_out_duration", 0, 10000);
    if (fade_time == FS_CONFIG_NONE) {
        fade_time = 750;
    }
    fade_time = fade_time * 1000;

    int64_t dt = fs_emu_monotonic_time() - g_fs_emu_quit_time;
    if (dt > fade_time && g_fs_emu_emulation_thread_stopped) {
        fs_emu_log("calling fs_ml_stop because emu thread is done\n");
        fs_ml_stop();

    }
    else if (dt > 5 * 1000 * 1000) {

        fs_emu_log("calling fs_ml_stop because emu does not stop\n");

        fs_ml_stop();
        fs_emu_log("force-closing the emulator\n");
        exit(1);
    }


    float fade = (1.0 * dt) / fade_time;
    if (fade > 1.0) {
        fade = 1.0;
    }


    fs_gl_viewport(0, 0, fs_ml_video_width(), fs_ml_video_height());
    fs_gl_ortho_hd();
    fs_gl_blending(1);
    fs_gl_texturing(0);
    fs_gl_color4f(g_fs_emu_theme.fade_color[0] * fade,
            g_fs_emu_theme.fade_color[1] * fade,
            g_fs_emu_theme.fade_color[2] * fade, fade);

#ifdef USE_GLES
    GLfloat vert[] = {
        0, 0,
        1920, 0,
        1920, 1080,
        0, 1080
    };

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(2, GL_FLOAT, 0, vert);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glDisableClientState(GL_VERTEX_ARRAY);
#else
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(1920, 0);
    glVertex2f(1920, 1080);
    glVertex2f(0, 1080);
    glEnd();
#endif

    CHECK_GL_ERROR();
}
