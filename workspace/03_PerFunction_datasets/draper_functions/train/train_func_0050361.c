write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    mgr->writeKey(S, fCloneKey);
    mgr->writeKey(S, fRequestorKey);
    S->writeInt(fOriginatingPlayerID);
    S->writeInt(fUserData);
    S->writeByte(fValidMsg);
    S->writeByte(fIsLoading);
    mgr->WriteCreatable(S, fTriggerMsg);
}
