write(hsStream* S, plResManager* mgr) {
    plLayerAnimation::write(S, mgr);

    mgr->writeKey(S, fLinkKey);
    S->writeBool(fLeavingAge);
}
