mk_knox_portal(xchar x, xchar y)
{
    extern int n_dgns;
    d_level *source;
    branch *br;
    schar u_depth;

    br = dungeon_branch("Fort Ludios");
    if (on_level(&knox_level, &br->end1))
    {
        source = &br->end2;
    }
    else
    {

        if(Is_branchlev(&u.uz))
                return;
        source = &br->end1;
    }


    if (source->dnum < n_dgns || (rn2(3)
#ifdef WIZARD
                                  && !wizard
#endif
                                 )) return;

    if (! (u.uz.dnum == oracle_level.dnum
           && !at_dgn_entrance("The Quest")
           && (u_depth = depth(&u.uz)) > 10
           && u_depth < depth(&medusa_level)))
            return;


    *source = u.uz;
    insert_branch(br, true);

#ifdef DEBUG
    pline("Made knox portal.");
#endif
    place_branch(br, x, y);
}
