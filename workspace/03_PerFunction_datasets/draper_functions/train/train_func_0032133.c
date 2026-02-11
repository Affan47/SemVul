NewAttributeC (
    const Char *        name,
    Int                 narg,
    const Char *        nams,
    ObjFunc             hdlr )
{
    Obj                 getter;
    Obj                 setter;
    Obj                 tester;
    Int                 flag2;
    Obj                 fname;

    flag2 = ++CountFlags;


    C_NEW_STRING(fname, strlen(name), name);
    setter = MakeSetter(fname, flag2);
    tester = MakeTester(fname, flag2);

    getter = NewOperationC( name, 1L, nams, (hdlr ? hdlr : DoAttribute) );

    SetupAttribute(getter, setter, tester, flag2);

    return getter;
}
