unmanageClient(Window win, bool mapClient,
                                    bool reparent) {
    YFrameWindow *frame = findFrame(win);

    MSG(("unmanaging window 0x%lX", win));

    if (frame) {
        YFrameClient *client = frame->client();


        client->hide();

        frame->hide();
        frame->unmanage(reparent);
        delete frame;

        if (mapClient)
            client->show();
        delete client;
    } else {
        MSG(("unmanage: unknown window: 0x%lX", win));
    }
}
