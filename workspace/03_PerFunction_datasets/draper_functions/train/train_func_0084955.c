observe_quantum_cat(struct obj *box)
{
    static const char sc[] = "Schroedinger's Cat";
    struct obj *deadcat;
    struct monst *livecat;
    xchar ox, oy;

    box->spe = 0;
    if (get_obj_location(box, &ox, &oy, 0))
    {
        box->ox = ox, box->oy = oy;
    }


    livecat = rn2(2) ? makemon(&mons[PM_HOUSECAT],
                               box->ox, box->oy, NO_MINVENT) : 0;
    if (livecat)
    {
        livecat->mpeaceful = 1;
        set_malign(livecat);
        if (!canspotmon(livecat))
        {
            You("think %s brushed your %s.", something, body_part(FOOT));
        }
        else
        {
            pline("%s inside the box is still alive!", Monnam(livecat));
        }
        christen_monst(livecat, sc);
    }
    else
    {
        deadcat = mk_named_object(CORPSE, &mons[PM_HOUSECAT],
                                  box->ox, box->oy, sc);
        if (deadcat)
        {
            obj_extract_self(deadcat);
            add_to_container(box, deadcat);
        }
        pline_The("%s inside the box is dead!",
                  Hallucination ? rndmonnam() : "housecat");
    }
    box->owt = weight(box);
    return;
}
