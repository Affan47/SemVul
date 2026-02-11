client_present(ObClient *self, gboolean here, gboolean raise,
                           gboolean unshade)
{
    if (client_normal(self) && screen_showing_desktop)
        screen_show_desktop(FALSE, self);
    if (self->iconic)
        client_iconify(self, FALSE, here, FALSE);
    if (self->desktop != DESKTOP_ALL &&
        self->desktop != screen_desktop)
    {
        if (here)
            client_set_desktop(self, screen_desktop, FALSE, TRUE);
        else
            screen_set_desktop(self->desktop, FALSE);
    } else if (!self->frame->visible)


        return;
    if (self->shaded && unshade)
        client_shade(self, FALSE);
    if (raise)
        stacking_raise(CLIENT_AS_WINDOW(self));

    client_focus(self);
}
