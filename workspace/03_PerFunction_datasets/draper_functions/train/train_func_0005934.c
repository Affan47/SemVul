showClient(Window win, bool showClient) {
    for (int i = 0; i < fDocked.getCount(); i++) {
        YXTrayEmbedder *ec = fDocked[i];
        if (ec->client_handle() == win) {
            ec->fVisible = showClient;
            if (showClient)
                ec->show();
            else
                ec->hide();
        }
    }
    relayout();
}
