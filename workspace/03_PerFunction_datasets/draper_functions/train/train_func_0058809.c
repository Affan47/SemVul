GetCharBBox(struct MacFontRec *font, int ch, Rect *bbox ) {
    unsigned short *widths = font->offsetWidths;
    unsigned short *locs = font->locs;
    unsigned short *rows = font->fontImage;
    int i;
    int ow;

    ch -= font->firstChar;
    ow = widths[ch];
    bbox->left = (ow>>8)+font->kernMax; bbox->width = locs[ch+1]-locs[ch];
    bbox->height = font->fRectHeight; bbox->bottom = -font->descent;
    for ( i=0; i<font->fRectHeight; ++i )
	if ( AnyBitsSet(rows+i*font->rowWords,locs[ch],locs[ch+1]) )
    break;
    bbox->height -= i;
    for ( i=0; i<bbox->height; ++i )
	if ( AnyBitsSet(rows+(font->fRectHeight-i-1)*font->rowWords,locs[ch],locs[ch+1]) )
    break;
    bbox->bottom += i; bbox->height -= i;
    if ( bbox->height<0 ) bbox->height = 0;
return( ow&0xff );
}
