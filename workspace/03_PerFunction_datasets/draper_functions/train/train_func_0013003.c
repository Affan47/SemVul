_parse_app_info(BITSTREAM *bs, INDX_APP_INFO *app_info)
{
    uint32_t len;

    bs_seek_byte(bs, 40);

    len = bs_read(bs, 32);

    if (len != 34) {
        BD_DEBUG(DBG_NAV, "index.bdmv app_info length is %d, expected 34 !\n", len);
    }

    bs_skip(bs, 1);
    app_info->initial_output_mode_preference = bs_read(bs, 1);
    app_info->content_exist_flag             = bs_read(bs, 1);
    bs_skip(bs, 5);

    app_info->video_format = bs_read(bs, 4);
    app_info->frame_rate   = bs_read(bs, 4);

    bs_read_bytes(bs, app_info->user_data, 32);

    return 1;
}
