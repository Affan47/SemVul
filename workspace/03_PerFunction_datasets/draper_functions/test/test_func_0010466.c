destroyNotifyEvent(XDestroyWindowEvent &de) {
    if (de.window == m_client->window()) {
        fbdbg<<"DestroyNotifyEvent this="<<this<<" title = "<<title().logical()<<endl;
        delete m_client;
        if (numClients() == 0)
            delete this;
    }

}
