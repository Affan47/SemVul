gli_get_hyperlink(unsigned int x, unsigned int y)
{
    if (!gli_mask || !gli_mask->hor || !gli_mask->ver)
    {
        gli_strict_warning("get_hyperlink: struct not initialized");
        return 0;
    }

    if (x >= gli_mask->hor
            || y >= gli_mask->ver
            || !gli_mask->links[x])
    {
        gli_strict_warning("get_hyperlink: invalid range given");
        return 0;
    }

    return gli_mask->links[x][y];
}
