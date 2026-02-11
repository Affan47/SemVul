uset_cleanup(void) {
    for(int32_t i = UPROPS_SRC_NONE; i < UPROPS_SRC_COUNT; ++i) {
        Inclusion &in = gInclusions[i];
        delete in.fSet;
        in.fSet = NULL;
        in.fInitOnce.reset();
    }

    delete uni32Singleton;
    uni32Singleton = NULL;
    uni32InitOnce.reset();
    return TRUE;
}
