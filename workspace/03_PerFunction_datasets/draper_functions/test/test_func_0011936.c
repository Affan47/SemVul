c_tweak(struct state *st, int base, int tweak)
{
    int ranTweak = (random() % (2 * tweak));
    int n = (base + (ranTweak - tweak));
    if (n < 0) n = -n;
    return (n < 255 ? n : 255);
}
