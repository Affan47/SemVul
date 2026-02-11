xcf_calc_levels(int size, int tile_size)
{
    int levels = 1;
    while (size > tile_size) {
        size >>= 1;
        levels++;
    }
    return levels;
}
