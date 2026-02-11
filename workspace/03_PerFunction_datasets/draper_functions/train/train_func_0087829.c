flash_timeout(gpointer data)
{
    ObFrame *self = data;
    GTimeVal now;

    g_get_current_time(&now);
    if (now.tv_sec > self->flash_end.tv_sec ||
        (now.tv_sec == self->flash_end.tv_sec &&
         now.tv_usec >= self->flash_end.tv_usec))
        self->flashing = FALSE;

    if (!self->flashing)
        return FALSE;

    self->flash_on = !self->flash_on;
    if (!self->focused) {
        frame_adjust_focus(self, self->flash_on);
        self->focused = FALSE;
    }

    return TRUE;
}
