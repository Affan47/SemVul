SCMakeBaseReference(SplineChar *sc,SplineFont *sf,int layer,int ch, BDFFont *bdf,int disp_only) {
    SplineChar *rsc;
    BDFChar *bc;
    char *dot;
    char buffer[200], namebuf[200];

    if ( (dot = strchr(sc->name,'.'))!=NULL ) {
	snprintf(buffer,sizeof(buffer),"%s%s",
		(char *) StdGlyphName(namebuf,ch,sf->uni_interp,sf->for_new_glyphs),
		dot);
	rsc = SFGetChar(sf,-1,buffer);
    } else
	rsc = SFGetChar(sf,ch,NULL);

    if ( rsc==NULL && dot==NULL ) {
	if ( ch==0x131 || ch==0xf6be || ch==0x237) {
	    if ( ch==0x131 ) ch='i'; else ch = 'j';
	    rsc = SFGetChar(sf,ch,NULL);
	    if ( rsc!=NULL && !sf->dotlesswarn ) {


		ff_post_error( _("Missing Glyph..."),ch=='i'?_("Your font is missing the dotlessi glyph,\nplease add it and remake your accented glyphs"):


			_("Your font is missing the uni0237 glyph,\nand the deprecated dotlessj glyph,\nplease add the former and remake your accented glyphs"));
		sf->dotlesswarn = true;
	    }
	}
    }
    if ( rsc==NULL )
return( 0 );
    if ( bdf == NULL || !disp_only ) {
	sc->width = rsc->width;
	if ( ch!=' ' )
	    SCAddRef(sc,rsc,layer,0,0);
    }
    if ( !disp_only ) {
	for ( bdf=sf->cidmaster?sf->cidmaster->bitmaps:sf->bitmaps; bdf!=NULL; bdf=bdf->next ) {
	    if ( bdf->glyphs[rsc->orig_pos] != NULL ) {
		if (( bc = bdf->glyphs[sc->orig_pos] ) == NULL ) {
		    bc = BDFMakeGID(bdf,sc->orig_pos);
		    BCClearAll( bc );
		}
		if ( ch!=' ' )
		    BCAddReference( bc,bdf->glyphs[rsc->orig_pos],rsc->orig_pos,0,0 );
	    }
	}
    } else if ( bdf != NULL ) {
	if ( bdf->glyphs[rsc->orig_pos] != NULL ) {
	    if (( bc = bdf->glyphs[sc->orig_pos] ) == NULL ) {
		bc = BDFMakeGID(bdf,sc->orig_pos);
		BCClearAll( bc );
	    }
	    if ( ch!=' ' )
		BCAddReference( bc,bdf->glyphs[rsc->orig_pos],rsc->orig_pos,0,0 );
	}
    }
return( 1 );
}
