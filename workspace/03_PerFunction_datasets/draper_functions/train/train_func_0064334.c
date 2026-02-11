doRaise() {
#ifdef DEBUG
    if (debug_z) dumpZorder("wmRaise: ", this);
#endif
    if (this != manager->top(getActiveLayer())) {
        setAbove(manager->top(getActiveLayer()));

        {
            for (YFrameWindow * w (transient()); w; w = w->nextTransient())
                w->doRaise();
        }

        if (client() && client()->clientLeader() != 0) {
            YFrameWindow *o = manager->findFrame(client()->clientLeader());

            if (o != 0) {
                for (YFrameWindow * w (o->transient()); w; w = w->nextTransient())
                    w->doRaise();
            }

            if (client()->ownerWindow() != manager->handle()) {
                for (YFrameWindow * w = manager->bottomLayer(); w; w = w->prevLayer())
                {
                    if (w->client() && w->client()->clientLeader() == client()->clientLeader() && w->client()->ownerWindow() == manager->handle())
                        w->doRaise();
                }
            }
        }

#ifdef DEBUG
        if (debug_z) dumpZorder("wmRaise after raise: ", this);
#endif
    }
}
