Tdelo (Tobj to, Tobj ko) {
    if (!to || !ko)
        return;
    if (!T_ISTABLE (to))
        panic1 (POS, "Tdelo", "delete attempted on non-table");
    if (!(T_ISINTEGER (ko) || T_ISREAL (ko) || T_ISSTRING (ko)))
        panic1 (POS, "Tdelo", "bad key");
    delete (to, ko, NULL);
}
