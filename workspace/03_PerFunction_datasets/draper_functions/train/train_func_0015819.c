IsTablePlist (
    Obj                 list )
{
    Int                 ktype;
    ktype = KTNumPlist( list, (Obj *)0 );
    return (T_PLIST_TAB <= ktype && ktype <= T_PLIST_TAB_RECT_SSORT);
}
