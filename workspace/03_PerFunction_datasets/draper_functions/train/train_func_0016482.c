NewAttribute (
    Obj                 name,
    Int                 narg,
    Obj                 nams,
    ObjFunc             hdlr )
{
    Obj                 getter;
    Obj                 setter;
    Obj                 tester;
    Int                 flag2;

    flag2 = ++CountFlags;
    setter = MakeSetter(name, flag2);
    tester = MakeTester(name, flag2);

    getter = NewOperation( name, 1L, nams, (hdlr ? hdlr : DoAttribute) );

    SetupAttribute(getter, setter, tester, flag2);

    return getter;
}
