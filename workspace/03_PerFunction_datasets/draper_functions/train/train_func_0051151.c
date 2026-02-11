write(hsStream* S, plResManager* mgr) {
    S->writeShort(fVolumes.getSize());
    for (size_t i=0; i<fVolumes.getSize(); i++)
        mgr->WriteCreatable(S, fVolumes[i]);
}
