place_level(int proto_index, struct proto_dungeon *pd)
{
    bool map[MAXLEVEL+1];
    s_level *lev;
    int npossible;
#ifdef DDEBUG
    int i;
#endif

    if (proto_index == pd->n_levs) return true;

    lev = pd->final_lev[proto_index];


    if (!lev) return place_level(proto_index+1, pd);

    npossible = possible_places(proto_index, map, pd);

    for (; npossible; --npossible)
    {
        lev->dlevel.dlevel = pick_level(map, rn2(npossible));
#ifdef DDEBUG
        indent(proto_index-pd->start);
        fprintf(stderr,"%s: trying %d [ ", lev->proto, lev->dlevel.dlevel);
        for (i = 1; i <= MAXLEVEL; i++)
                if (map[i]) fprintf(stderr,"%d ", i);
        fprintf(stderr,"]\n");
#endif
        if (place_level(proto_index+1, pd)) return true;
        map[lev->dlevel.dlevel] = false;
    }
#ifdef DDEBUG
    indent(proto_index-pd->start);
    fprintf(stderr,"%s: failed\n", lev->proto);
#endif
    return false;
}
