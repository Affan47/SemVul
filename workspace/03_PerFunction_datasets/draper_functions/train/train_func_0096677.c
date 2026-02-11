IRead(hsStream* S, plResManager* mgr) {
    fOfferer = mgr->readKey(S);
    fTargetAge = S->readInt();
    fOfferee = S->readInt();
}
