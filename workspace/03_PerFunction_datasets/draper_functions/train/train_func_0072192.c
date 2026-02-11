IRead(hsStream* S, plResManager* mgr) {
    fStage = S->readInt();
    fEvent = S->readInt();
    fAvatar = mgr->readKey(S);
}
