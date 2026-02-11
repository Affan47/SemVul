scale_bitcount(const lame_internal_flags * gfc, gr_info * cod_info)
{
    if (gfc->cfg.mode_gr == 2) {
        return mpeg1_scale_bitcount(gfc, cod_info);
    }
    else {
        return mpeg2_scale_bitcount(gfc, cod_info);
    }
}
