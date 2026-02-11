adjabil(int oldlevel, int newlevel)
{
    const struct innate *abil, *rabil;
    long mask = FROMEXPER;


    switch (Role_switch)
    {
    case PM_ARCHEOLOGIST:
        abil = arc_abil;	break;
    case PM_BARBARIAN:
        abil = bar_abil;	break;
    case PM_CAVEMAN:
        abil = cav_abil;	break;
    case PM_HEALER:
        abil = hea_abil;	break;
    case PM_KNIGHT:
        abil = kni_abil;	break;
    case PM_MONK:
        abil = mon_abil;	break;
    case PM_PRIEST:
        abil = pri_abil;	break;
    case PM_RANGER:
        abil = ran_abil;	break;
    case PM_ROGUE:
        abil = rog_abil;	break;
    case PM_SAMURAI:
        abil = sam_abil;	break;
    case PM_TOURIST:
        abil = tou_abil;	break;
    case PM_VALKYRIE:
        abil = val_abil;	break;
    case PM_WIZARD:
        abil = wiz_abil;	break;
    default:
        abil = 0;		break;
    }

    switch (Race_switch)
    {
    case PM_ELF:
        rabil = elf_abil;	break;
    case PM_ORC:
        rabil = orc_abil;	break;
    case PM_HUMAN:
    case PM_DWARF:
    case PM_GNOME:
    default:
        rabil = 0;		break;
    }

    while (abil || rabil)
    {
        long prevabil;

        if (!abil || !abil->ability)
        {

            if (!rabil || !rabil->ability)
            {
                break;
            }
            abil = rabil;
            rabil = 0;
            mask = FROMRACE;
        }
        prevabil = *(abil->ability);
        if (oldlevel < abil->ulevel && newlevel >= abil->ulevel)
        {


            if (abil->ulevel == 1)
                    *(abil->ability) |= (mask|FROMOUTSIDE);
            else
                    *(abil->ability) |= mask;
            if (!(*(abil->ability) & INTRINSIC & ~mask))
            {
                if (*(abil->gainstr))
                        You_feel("%s!", abil->gainstr);
            }
        }
        else if (oldlevel >= abil->ulevel && newlevel < abil->ulevel)
        {
            *(abil->ability) &= ~mask;
            if (!(*(abil->ability) & INTRINSIC))
            {
                if (*(abil->losestr))
                        You_feel("%s!", abil->losestr);
                else if (*(abil->gainstr))
                        You_feel("less %s!", abil->gainstr);
            }
        }
        if (prevabil != *(abil->ability))
                postadjabil(abil->ability);
        abil++;
    }

    if (oldlevel > 0)
    {
        if (newlevel > oldlevel)
                add_weapon_skill(newlevel - oldlevel);
        else
                lose_weapon_skill(oldlevel - newlevel);
    }
}
