os_set_window_frame(void)
{
    WINDOW_WIDTH=min(screen->w,FIELD_WIDTH);
    WINDOW_HEIGHT=min(screen->h,FIELD_HEIGHT);
}
