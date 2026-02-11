mprSetManager(void *ptr, void *manager)
{
    MprMem      *mp;

    mp = GET_MEM(ptr);
    mprAssert(HAS_MANAGER(mp));
    if (HAS_MANAGER(mp)) {
        if (!manager) {
            manager = dummyManager;
        }
        SET_MANAGER(mp, manager);
    }
    return ptr;
}
