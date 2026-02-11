GlyphVariantsFree(struct glyphvariants *gv) {
    int i;

    if ( gv==NULL )
return;
    free(gv->variants);
#ifdef FONTFORGE_CONFIG_DEVICETABLES
    DeviceTableFree(gv->italic_adjusts);
#endif
    for ( i=0; i<gv->part_cnt; ++i )
	free( gv->parts[i].component );
    free(gv->parts);
    chunkfree(gv,sizeof(*gv));
}
