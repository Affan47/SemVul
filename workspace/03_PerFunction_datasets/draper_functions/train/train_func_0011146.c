run_func(ObActionsData *data, gpointer options)
{
    Options *o = options;

    if (data->client) {
        ObClient *c = data->client;
        guint32 corner;

        if (!data->button)
            corner = OBT_PROP_ATOM(NET_WM_MOVERESIZE_SIZE_KEYBOARD);
        else if (o->corner_specified)
            corner = o->corner;
        else
            corner = pick_corner(data->x, data->y,
                                 c->frame->area.x, c->frame->area.y,


                                 c->area.width + c->frame->size.left +
                                 c->frame->size.right,
                                 c->area.height + c->frame->size.top +
                                 c->frame->size.bottom, c->shaded);

        moveresize_start(c, data->x, data->y, data->button, corner);
    }

    return FALSE;
}
