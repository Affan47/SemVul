setblockto (lev_t * level, const unsigned x, const unsigned y, const char c)
{
    if (!(x < LEVWIDTH && y < LEVHEIGHT))
        return;
    (*level)[y][x] = c;
}
