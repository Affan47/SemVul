ReadXConnectMessage (XIMS ims, XClientMessageEvent *ev)
{
    Xi18n i18n_core = ims->protocol;
    XSpecRec *spec = (XSpecRec *) i18n_core->address.connect_addr;
    XEvent event;
    Display *dpy = i18n_core->address.dpy;
    Window new_client = ev->data.l[0];
    CARD32 major_version = ev->data.l[1];
    CARD32 minor_version = ev->data.l[2];
    XClient *x_client = NewXClient (i18n_core, new_client);

    if (ev->window != i18n_core->address.im_window)
        return;

    if (major_version != 0  ||  minor_version != 0)
    {
        major_version =
        minor_version = 0;

    }

    _XRegisterFilterByType (dpy,
                            x_client->accept_win,
                            ClientMessage,
                            ClientMessage,
                            WaitXIMProtocol,
                            (XPointer)ims);
    event.xclient.type = ClientMessage;
    event.xclient.display = dpy;
    event.xclient.window = new_client;
    event.xclient.message_type = spec->connect_request;
    event.xclient.format = 32;
    event.xclient.data.l[0] = x_client->accept_win;
    event.xclient.data.l[1] = major_version;
    event.xclient.data.l[2] = minor_version;
    event.xclient.data.l[3] = XCM_DATA_LIMIT;

    XSendEvent (dpy,
                new_client,
                False,
                NoEventMask,
                &event);
    XFlush (dpy);
}
