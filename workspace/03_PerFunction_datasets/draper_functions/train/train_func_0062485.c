get_threaded_info( StgPtr p )
{
    StgWord q;

    q = (W_)GET_INFO(UNTAG_CLOSURE((StgClosure *)p));

loop:
    switch (GET_CLOSURE_TAG((StgClosure *)q))
    {
    case 0:
        ASSERT(LOOKS_LIKE_INFO_PTR(q));
        return q;
    case 1:
    {
        StgWord r = *(StgPtr)(q-1);
        ASSERT(LOOKS_LIKE_INFO_PTR((StgWord)UNTAG_CLOSURE((StgClosure *)r)));
        return r;
    }
    case 2:
        q = *(StgPtr)(q-2);
        goto loop;
    default:
        barf("get_threaded_info");
    }
}
