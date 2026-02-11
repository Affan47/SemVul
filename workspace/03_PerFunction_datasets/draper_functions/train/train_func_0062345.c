Tdels (Tobj to, char *sk) {
    if (!to)
        return;
    if (!T_ISTABLE (to))
        panic1 (POS, "Tdels", "delete attempted on non-table");
    delete (to, &keys, sk);
}
