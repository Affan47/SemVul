frame_end_iconify_animation(ObFrame *self)
{

    if (self->iconify_animation_going == 0) return;

    if (!self->visible)
        XUnmapWindow(obt_display, self->window);
    else {


        client_reconfigure(self->client, TRUE);
    }


    self->iconify_animation_going = 0;

    XMoveResizeWindow(obt_display, self->window,
                      self->area.x, self->area.y,
                      self->area.width, self->area.height);

    framerender_frame(self);
    XFlush(obt_display);
}
