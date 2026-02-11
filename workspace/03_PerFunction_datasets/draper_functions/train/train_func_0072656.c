get_cost(struct obj *obj, struct monst *shkp)
{
    long tmp = getprice(obj, false);

    if (!tmp) tmp = 5L;


    if (!obj->dknown || !objects[obj->otyp].oc_name_known)
    {
        if (obj->oclass == GEM_CLASS &&
            objects[obj->otyp].oc_material == GLASS)
        {
            int i;


            bool pseudorand =
                (((int)u.ubirthday % obj->otyp) >= obj->otyp/2);


            switch(obj->otyp - LAST_GEM)
            {
            case 1:
                i = pseudorand ? DIAMOND : OPAL;
                break;
            case 2:
                i = pseudorand ? SAPPHIRE : AQUAMARINE;
                break;
            case 3:
                i = pseudorand ? RUBY : JASPER;
                break;
            case 4:
                i = pseudorand ? AMBER : TOPAZ;
                break;
            case 5:
                i = pseudorand ? JACINTH : AGATE;
                break;
            case 6:
                i = pseudorand ? CITRINE : CHRYSOBERYL;
                break;
            case 7:
                i = pseudorand ? BLACK_OPAL : JET;
                break;
            case 8:
                i = pseudorand ? EMERALD : JADE;
                break;
            case 9:
                i = pseudorand ? AMETHYST : FLUORITE;
                break;
            default: impossible("bad glass gem %d?", obj->otyp);
                     i = STRANGE_OBJECT;
                     break;
            }
            tmp = (long) objects[i].oc_cost;
        }
        else if (!(obj->o_id % 4))
                tmp += tmp / 3L;
    }
    if ((Role_if(PM_TOURIST) && u.ulevel < (MAXULEV/2))
        || (uarmu && !uarm && !uarmc))
            tmp += tmp / 3L;
    else
            if (uarmh && uarmh->otyp == DUNCE_CAP)
                    tmp += tmp / 3L;

    if (ACURR(A_CHA) > 18)		tmp /= 2L;
    else if (ACURR(A_CHA) > 17)	tmp -= tmp / 3L;
    else if (ACURR(A_CHA) > 15)	tmp -= tmp / 4L;
    else if (ACURR(A_CHA) < 6)	tmp *= 2L;
    else if (ACURR(A_CHA) < 8)	tmp += tmp / 2L;
    else if (ACURR(A_CHA) < 11)	tmp += tmp / 3L;
    if (tmp <= 0L) tmp = 1L;
    else if (obj->oartifact) tmp *= 4L;

    if (shkp && ESHK(shkp)->surcharge) tmp += (tmp + 2L) / 3L;
    return tmp;
}
