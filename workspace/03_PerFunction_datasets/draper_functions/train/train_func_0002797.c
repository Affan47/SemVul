wmCloseSession() {
    for (YFrameWindow * f(topLayer()); f; f = f->nextLayer())
        if (f->client()->adopted())
            f->wmClose();
}
