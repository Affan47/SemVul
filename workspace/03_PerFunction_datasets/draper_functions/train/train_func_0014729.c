ufraw_convert_image_vignetting(ufraw_data *uf,
        ufraw_image_data *img, UFRectangle *area)
{

    if (uf->modFlags & LF_MODIFY_VIGNETTING)
        lf_modifier_apply_color_modification(
            uf->modifier, img->buffer,
            area->x, area->y, area->width, area->height,
            LF_CR_4(RED, GREEN, BLUE, UNKNOWN), img->rowstride);
}
