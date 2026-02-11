gonzo_library_append(const char *s)
{
    gonzo_ty        *gp;
    string_ty       *tmp;
    string_ty       *dir;


    trace(("gonzo_library_append(s = \"%s\")\n{\n", s));
    assert(s);
    assert(!done_tail);
    tmp = str_from_c(s);
    os_become_orig();
    dir = os_pathname(tmp, 1);
    os_become_undo();
    str_free(tmp);


    gp = (gonzo_ty *)mem_alloc_clear(sizeof(gonzo_ty));
    gp->dir = dir;
    gp->temporary = is_temporary(dir);
    gp->gstate_filename = str_format("%s/state", gp->dir->str_text);
    trace(("gonzo = %08lX;\n", (long)gonzo));
    trace(("ngonzos = %ld;\n", (long)ngonzos));

    if (ngonzos >= ngonzos_max)
    {
        ngonzos_max = ngonzos_max * 2 + 4;
        gonzo_ty **new_gonzo = new gonzo_ty * [ngonzos_max];
        for (size_t k = 0; k < ngonzos; ++k)
            new_gonzo[k] = gonzo[k];
        delete [] gonzo;
        gonzo = new_gonzo;
    }
    gonzo[ngonzos++] = gp;
    trace(("}\n"));
}
