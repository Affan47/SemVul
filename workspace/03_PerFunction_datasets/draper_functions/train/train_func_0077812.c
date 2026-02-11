doprwep(void)
{
    if (!uwep) {
        You("are empty %s.", body_part(HANDED));
    } else {
        prinv((char *)0, uwep, 0L);
        if (u.twoweap) prinv((char *)0, uswapwep, 0L);
    }
    return 0;
}
