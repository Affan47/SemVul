read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);

    if (S->getVer().isUru()) {

        fProps.read(S);
        S->readInt();
    }
    fPhysical = mgr->readKey(S);
}
