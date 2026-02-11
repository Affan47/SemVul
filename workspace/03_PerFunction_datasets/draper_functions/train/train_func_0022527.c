borg_prayer_okay(int book, int what)
{
    int reserve_mana =0;

    borg_magic *as = &borg_magics[book][what];


    if (no_light()) return (FALSE);


    if (borg_class == CLASS_PRIEST) reserve_mana = 8;
    if (borg_class == CLASS_PALADIN) reserve_mana = 20;


    if (borg_skill[BI_CLEVEL] < 35) reserve_mana = 0;


    if (!borg_prayer_legal(book, what)) return (FALSE);


    if (borg_skill[BI_ISBLIND] || borg_skill[BI_ISCONFUSED]) return (FALSE);


    if (as->power > borg_skill[BI_CURSP]) return (FALSE);


    if (borg_skill[BI_CURSP] - as->power < reserve_mana)
    {

        if (book == 1 && what == 1) return (TRUE);
        if (book == 4 && what == 0) return (TRUE);


        if (book == 4 && what == 1) return (TRUE);


        if (book == 1 && what == 5) return (TRUE);


        if (book == 8 && what == 2) return (TRUE);


        return (FALSE);
    }


    return (TRUE);
}
