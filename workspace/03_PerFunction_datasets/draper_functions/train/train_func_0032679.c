read(hsStream* S, plResManager* mgr) {
    plCameraBrain1::read(S, mgr);

    fCircleFlags = S->readInt();
    fCenter.read(S);
    fRadius = S->readFloat();
    fCenterObject = mgr->readKey(S);
    fPOAObject = mgr->readKey(S);
    fCirPerSec = S->readFloat();
}
