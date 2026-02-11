tga_swap_red_blue(tga_image *img)
{
    uint8_t *ptr;
    uint8_t bpp = img->pixel_depth / 8;

    if (!UNMAP_DEPTH(img->pixel_depth)) return TGAERR_PIXEL_DEPTH;

    for (ptr = img->image_data;
         ptr < img->image_data + (img->width * img->height - 1) * bpp;
         ptr += bpp)
    {
        uint8_t r,g,b,a;
        (void)tga_unpack_pixel(ptr, img->pixel_depth, &b,&g,&r,&a);
        (void)tga_pack_pixel(ptr, img->pixel_depth, r,g,b,a);
    }
    return TGA_NOERR;
}
