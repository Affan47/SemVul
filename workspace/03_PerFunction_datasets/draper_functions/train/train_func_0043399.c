Tinso (Tobj to, Tobj ko, Tobj vo) {
    long tm;

    if (!to || !T_ISTABLE (to))
        panic1 (POS, "Tinso", "insert attempted on non-table");
    if (!ko || !(T_ISINTEGER (ko) || T_ISREAL (ko) || T_ISSTRING (ko)))
        panic1 (POS, "Tinso", "bad key");
    tm = Mpushmark (to);
    Mpushmark (ko);
    if (vo)
        Mpushmark (vo);
    insert (to, ko, NULL, vo);
    Mpopmark (tm);
}
