Read(hsStream* S, plResManager* mgr) {
    proEventData* event = ICreateEventDataType(S->readInt());
    if (event != NULL)
        event->IRead(S, mgr);
    return event;
}
