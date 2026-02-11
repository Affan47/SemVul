GC_add_roots(void *b, void *e)
{
    DCL_LOCK_STATE;

    if (!EXPECT(GC_is_initialized, TRUE)) GC_init();
    LOCK();
    GC_add_roots_inner((ptr_t)b, (ptr_t)e, FALSE);
    UNLOCK();
}
