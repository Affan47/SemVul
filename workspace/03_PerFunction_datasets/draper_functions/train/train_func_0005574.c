GFXmonitorfile (int fd) {
    Tobj fo, to, co;
    long fm, tm;

    if (!(fo = Tfinds (root, "monitorfile")) || Tgettype (fo) != T_CODE)
        return;

    fm = Mpushmark (fo);
    to = Ttable (4);
    tm = Mpushmark (to);
    Tinss (to, "fd", Tinteger (fd));
    if ((co = Pfcall (fo, to)))
        Eunit (co);
    Mpopmark (tm);
    Mpopmark (fm);
}
