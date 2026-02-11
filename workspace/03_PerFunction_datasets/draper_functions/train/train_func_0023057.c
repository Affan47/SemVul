screen_show_desktop(gboolean show, ObClient *show_only)
{
    GList *it;

    if (show == screen_showing_desktop) return;

    screen_showing_desktop = show;

    if (show) {

        for (it = g_list_last(stacking_list); it; it = g_list_previous(it)) {
            if (WINDOW_IS_CLIENT(it->data)) {
                ObClient *client = it->data;
                client_showhide(client);
            }
        }
    }
    else {

        for (it = stacking_list; it; it = g_list_next(it)) {
            if (WINDOW_IS_CLIENT(it->data)) {
                ObClient *client = it->data;
                if (client_should_show(client)) {
                    if (!show_only || client == show_only)
                        client_show(client);
                    else
                        client_iconify(client, TRUE, FALSE, TRUE);
                }
            }
        }
    }

    if (show) {

        for (it = focus_order; it; it = g_list_next(it)) {
            ObClient *c = it->data;
            if (c->type == OB_CLIENT_TYPE_DESKTOP &&
                (c->desktop == screen_desktop || c->desktop == DESKTOP_ALL) &&
                client_focus(it->data))
                break;
        }
    }
    else if (!show_only) {
        ObClient *c;

        if ((c = focus_fallback(TRUE, FALSE, TRUE, FALSE))) {


            if (c->can_focus) {


                frame_adjust_focus(c->frame, TRUE);
            }
        }
    }

    show = !!show;
    OBT_PROP_SET32(obt_root(ob_screen), NET_SHOWING_DESKTOP, CARDINAL, show);
}
