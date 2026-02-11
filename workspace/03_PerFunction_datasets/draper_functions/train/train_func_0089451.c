refs_check_space(const ref * bot, uint size, uint space)
{
    for (; size--; bot++)
        store_check_space(space, bot);
    return 0;
}
