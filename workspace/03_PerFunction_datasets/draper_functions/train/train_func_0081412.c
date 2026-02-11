write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    if (S->getVer().isUru())
        S->writeByte(fStreamVersion);
    fAgeLink.write(S, mgr);
    fLinkEffects.write(S);
    if (S->getVer().isNewPlasma())
        S->writeByte(fEoaUnknown);
}
