is_old_pixel_value(struct fillinfo *info, int x, int y)
{
    unsigned char *p = info->rgb + y * info->rowstride + x * info->pixelsize;
    unsigned char or, og, ob;
    or = *p;
    og = *(p + 1);
    ob = *(p + 2);
    if ((or == info->or) && (og == info->og) && (ob == info->ob))
    {
        return 1;
    }
    return 0;
}
