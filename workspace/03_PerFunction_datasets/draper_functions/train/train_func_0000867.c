Iremove (int argc, lvar_t *argv) {
    Tobj tblo, keyo;

    if (argc == 2)
        tblo = argv[1].o, keyo = argv[0].o;
    else
        tblo = root, keyo = argv[0].o;
    if (T_ISTABLE (tblo) && (T_ISNUMBER (keyo) || T_ISSTRING (keyo)))
        Tdelo (tblo, keyo);
    return L_SUCCESS;
}
