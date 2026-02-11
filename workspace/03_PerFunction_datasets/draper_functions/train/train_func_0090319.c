os_random_seed (void)
{
    if (user_random_seed == -1)

        return (time(0) & 0x7fff);
    return user_random_seed;
}
