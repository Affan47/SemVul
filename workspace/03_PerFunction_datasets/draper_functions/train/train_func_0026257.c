doprinuse(void)
{
    struct obj *otmp;
    int ct = 0;
    char lets[52+1];

    for (otmp = invent; otmp; otmp = otmp->nobj)
            if (is_worn(otmp) || tool_in_use(otmp))
                    lets[ct++] = obj_to_let(otmp);
    lets[ct] = '\0';
    if (!ct) You("are not wearing or wielding anything.");
    else display_inventory(lets, false);
    return 0;
}
