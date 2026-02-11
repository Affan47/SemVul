handle_unmap_event(XUnmapEvent *e)
{
    Client *c = find_client(e->window);
    Client *focus_to;

    if (!c)
        return;

    if (c->ignore_unmap)
        c->ignore_unmap--;
    else {


        focus_to = next_client_on_vdesk(c);
        remove_client(c, NOT_QUITTING);
        if (focus_to)
            focus_client(focus_to, NO_RAISE);
    }
}
