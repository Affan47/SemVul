read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);

    fLoadFlags = S->readInt();
    fCompFlags = S->readInt();
    fLayers.setSize(S->readInt());
    fPiggyBacks.setSize(S->readInt());

    for (size_t i=0; i<fLayers.getSize(); i++)
        fLayers[i] = mgr->readKey(S);
    for (size_t i=0; i<fPiggyBacks.getSize(); i++)
        fPiggyBacks[i] = mgr->readKey(S);
}
