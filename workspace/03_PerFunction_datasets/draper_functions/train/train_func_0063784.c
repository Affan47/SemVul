write(hsStream* S, plResManager* mgr) {
    if (!S->getVer().isNewPlasma()) {
        S->writeInt(0);
        S->writeBool(false);
        S->writeInt(0);
        S->writeFloat(0.0f);
        S->writeDouble(0.0);
    }
}
