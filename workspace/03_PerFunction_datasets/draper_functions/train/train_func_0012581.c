add_local_iddef(HSCPRC * hp, STRPTR id)
{
    INFILEPOS *fpos = new_infilepos(hp->inpf);
    HSCIDD *iddef = find_iddef(hp->project->document, id);

    DIHP(fprintf(stderr, DHL "add ref to id `%s' at `%s' (%lu,%lu)\n",
                 id, ifp_get_fname(fpos),
                 ifp_get_y(fpos), ifp_get_x(fpos)));


    if (iddef)
    {

        DIHP(fprintf(stderr, DHL "    duplicate definition\n"));

        hsc_message(hp, MSG_REDEFINE_ID,
                    "local id %q already declared", id);

        set_infilepos(hp->inpf, iddef->fpos);
        hsc_message(hp, MSG_REDEFINE_ID,
                    "(location of previous declaration)");

        set_infilepos(hp->inpf, fpos);
        del_infilepos(fpos);
    }
    else
    {

        iddef = app_iddef(hp->project->document, id);
        iddef->caller = fpos2caller(fpos);
        iddef->fpos = fpos;

        DIHP(fprintf(stderr, DHL "    append to local iddefs\n"));
    }

    return (TRUE);
}
