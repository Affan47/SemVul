get_user()
    const
{
    trace(("project_ty::get_user(this = %08lX)\n{\n", (long)this));
    if (!up)
    {
        fatal_raw
        (
            "%s: %d: project_ty::up not set, you should have called "
            "project_bind_existing or project_ty::bind_new() before now "
            "(bug)",
            __FILE__,
            __LINE__
        );
    }
    trace(("return %08lX;\n", (long)up.get()));
    trace(("}\n"));
    return up;
}
