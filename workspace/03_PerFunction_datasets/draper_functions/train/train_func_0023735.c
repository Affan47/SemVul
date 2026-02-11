wflush_collect_mb_strip_data(jxr_image_t image, int my)
{
    DEBUG("wflush_mb_strip: wflush_collect_mb_strip_data my=%d\n", my);

    int format_scale = 256;
    if (image->use_clr_fmt == 2 ) {
        format_scale = 16 + 8*15;
    } else if (image->use_clr_fmt == 1 ) {
        format_scale = 16 + 4*15;
    }

    int tx;
    for (tx = 0; tx < (int) image->tile_columns ; tx += 1) {
        int mx;
        for (mx = 0; mx < (int) image->tile_column_width[tx]; mx += 1) {
            int off = my * EXTENDED_WIDTH_BLOCKS(image) + image->tile_column_position[tx] + mx;
            int ch;
            for (ch = 0; ch < image->num_channels; ch += 1) {
                struct macroblock_s*mb = image->mb_row_buffer[ch] + off;
                MACROBLK_CUR_LP_QUANT(image,ch,tx,mx) = mb->lp_quant;
                MACROBLK_CUR(image,ch,tx,mx).hp_quant = mb->hp_quant;
                MACROBLK_CUR(image,ch,tx,mx).hp_cbp = mb->hp_cbp;
                MACROBLK_CUR(image,ch,tx,mx).hp_diff_cbp = mb->hp_diff_cbp;
                MACROBLK_CUR(image,ch,tx,mx).mbhp_pred_mode = mb->mbhp_pred_mode;
                MACROBLK_CUR(image,ch,tx,mx).hp_model_bits[0] = mb->hp_model_bits[0];
                MACROBLK_CUR(image,ch,tx,mx).hp_model_bits[1] = mb->hp_model_bits[1];
                int count = (ch==0)? 256 : format_scale;
                int idx;
                for (idx = 0 ; idx < count; idx += 1)
                    MACROBLK_CUR(image,ch,tx,mx).data[idx] = mb->data[idx];
                for (idx = 0 ; idx < 7 ; idx += 1)
                     MACROBLK_CUR(image,ch,tx,mx).pred_dclp[idx] = mb->pred_dclp[idx];
            }
            DEBUG("wflush_mb_strip: wflush_collect_mb_strip_data tx=%d, mx=%d, CUR=0x%08x UP1=0x%08x, UP2=0x%08x, UP3=0x%08x lp_quant=%d\n",
                tx, mx, MACROBLK_CUR(image,0,tx,mx).data[0],
                MACROBLK_UP1(image,0,tx,mx).data[0],
                MACROBLK_UP2(image,0,tx,mx).data[0],
                MACROBLK_UP3(image,0,tx,mx).data[0],
                MACROBLK_CUR_LP_QUANT(image,0,tx,mx));
        }
    }
}
