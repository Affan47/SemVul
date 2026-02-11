show_game_message(void)
{
    erase_screen(pause_bitmap);
    ui_drawbox(pause_bitmap,0,0,uirotwidth,uirotheight);
    ui_displaymessagewindow(pause_bitmap,pause_buffer);

    update_video_and_audio();

    if (input_ui_pressed(IPT_UI_CANCEL))
    {
        return 1;
    }

    if (code_pressed_memory(KEYCODE_O) || input_ui_pressed(IPT_UI_LEFT))
    {
        pause_done = 1;
    }
    else if (pause_done == 1 && (code_pressed_memory(KEYCODE_K) || input_ui_pressed(IPT_UI_RIGHT)))
    {
        pause_done = 2;
        return 1;
    }

    return 0;
}
