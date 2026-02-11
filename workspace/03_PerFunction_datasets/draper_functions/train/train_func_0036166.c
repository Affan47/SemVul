read(hsStream* S, plResManager* mgr) {
    plArmatureBrain::read(S, mgr);

    if (S->getVer().isMoul() || S->getVer().isUniversal())
        fIsCustomAvatar = S->readBool();
    else
        fIsCustomAvatar = false;
}
