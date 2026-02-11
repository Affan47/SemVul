__make_jxr(void)
{
    struct jxr_image*image = (struct jxr_image*) calloc(1, sizeof(struct jxr_image));
    image->user_flags = 0;
    image->width1 = 0;
    image->height1 = 0;
    image->extended_width = 0;
    image->extended_height = 0;
    image->header_flags1 = 0;
    image->header_flags2 = 0x80;
    image->header_flags_fmt = 0;
    image->bands_present = 0;
    image->num_channels = 0;
    image->tile_index_table = 0;
    image->tile_index_table_length = 0;
    image->primary = 1;

    clear_vlc_tables(image);

    int idx;
    for (idx = 0 ; idx < MAX_CHANNELS ; idx += 1) {
        image->strip[idx].up4 = 0;
        image->strip[idx].up3 = 0;
        image->strip[idx].up2 = 0;
        image->strip[idx].up1 = 0;
        image->strip[idx].cur = 0;
    }

    image->scaled_flag = 1;

    image->out_fun = 0;

    return image;
}
