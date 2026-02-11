SplineFontEmpty(void) {
    extern int default_fv_row_count, default_fv_col_count;
    time_t now;
    SplineFont *sf;

    sf = gcalloc(1,sizeof(SplineFont));
    sf->pfminfo.fstype = -1;
    sf->top_enc = -1;
    sf->macstyle = -1;
    sf->desired_row_cnt = default_fv_row_count; sf->desired_col_cnt = default_fv_col_count;
    sf->display_antialias = default_fv_antialias;
    sf->display_bbsized = default_fv_bbsized;
    sf->display_size = -default_fv_font_size;
    sf->display_layer = ly_fore;
    sf->sfntRevision = sfntRevisionUnset;
    sf->woffMajor = woffUnset;
    sf->woffMinor = woffUnset;
    sf->pfminfo.winascent_add = sf->pfminfo.windescent_add = true;
    sf->pfminfo.hheadascent_add = sf->pfminfo.hheaddescent_add = true;
    sf->pfminfo.typoascent_add = sf->pfminfo.typodescent_add = true;
    if ( TTFFoundry!=NULL )
	strncpy(sf->pfminfo.os2_vendor,TTFFoundry,4);
    else
	memcpy(sf->pfminfo.os2_vendor,"PfEd",4);
    sf->for_new_glyphs = DefaultNameListForNewFonts();
    time(&now);
    sf->creationtime = sf->modificationtime = now;

    sf->layer_cnt = 2;
    sf->layers = gcalloc(2,sizeof(LayerInfo));
    sf->layers[0].name = copy(_("Back"));
    sf->layers[0].background = true;
    sf->layers[1].name = copy(_("Fore"));
    sf->layers[1].background = false;
    sf->grid.background = true;

return( sf );
}
