previewgui_reset (GuPreviewGui* pc) {


    g_free (pc->uri);
    pc->uri = NULL;

    gummi->latex->modified_since_compile = TRUE;
    previewgui_stop_preview (pc);
    motion_do_compile (gummi->motion);

    if (config_get_value ("compile_status"))
        previewgui_start_preview (pc);
}
