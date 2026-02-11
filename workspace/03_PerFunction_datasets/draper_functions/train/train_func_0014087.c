dungeon_branch(s)
    const char *s;
{
    branch *br;
    xchar  dnum;

    dnum = dname_to_dnum(s);


    for (br = branches; br; br = br->next)
	if (br->end2.dnum == dnum) break;

    if (!br) panic("dgn_entrance: can't find entrance to %s", s);

    return br;
}
