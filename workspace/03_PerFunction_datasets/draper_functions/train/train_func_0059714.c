Find_Converter_To_C (char *name) {
    register CONVERTER *p;

    for (p = ctab; p < clast; p++)
        if (p->scheme_to_c && streq (p->name, name))
            return p->to_c;
    return 0;
}
