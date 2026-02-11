updateStats(lame_internal_flags * const gfc)
{
    SessionConfig_t const *const cfg = &gfc->cfg;
    EncResult_t *eov = &gfc->ov_enc;
    int     gr, ch;
    assert(0 <= eov->bitrate_index && eov->bitrate_index < 16);
    assert(0 <= eov->mode_ext && eov->mode_ext < 4);


    eov->bitrate_channelmode_hist[eov->bitrate_index][4]++;
    eov->bitrate_channelmode_hist[15][4]++;


    if (cfg->channels_out == 2) {
        eov->bitrate_channelmode_hist[eov->bitrate_index][eov->mode_ext]++;
        eov->bitrate_channelmode_hist[15][eov->mode_ext]++;
    }
    for (gr = 0; gr < cfg->mode_gr; ++gr) {
        for (ch = 0; ch < cfg->channels_out; ++ch) {
            int     bt = gfc->l3_side.tt[gr][ch].block_type;
            if (gfc->l3_side.tt[gr][ch].mixed_block_flag)
                bt = 4;
            eov->bitrate_blocktype_hist[eov->bitrate_index][bt]++;
            eov->bitrate_blocktype_hist[eov->bitrate_index][5]++;
            eov->bitrate_blocktype_hist[15][bt]++;
            eov->bitrate_blocktype_hist[15][5]++;
        }
    }
}
