create(int uid)
{


    trace(("user_ty::create(uid = %d)\n{\n", uid));
    user_ty::pointer old = pool_find(uid);
    if (old)
    {
        trace(("return %08lX;\n", (long)old.get()));
        trace(("}\n"));
        return old;
    }


    user_ty::pointer up(new user_ty(uid));
    pool_add(up);
    trace(("return %08lX;\n", (long)up.get()));
    trace(("}\n"));
    return up;
}
