DumpMacFont(FILE *resfile, struct macfont *macfont) {
    int size, i,j;
    long here;

    size = 13*sizeof(short) +
	    macfont->fRectHeight*macfont->rowWords*sizeof(short) +
	    258*sizeof(short) +
	    258*sizeof(short);
    macfont->owTLoc = (size- 258*sizeof(short)- (8*sizeof(short)))/

	    sizeof(short);

    here = ftell(resfile);
    putlong(0,resfile);
    putshort(macfont->fontType,resfile);
    putshort(macfont->firstChar,resfile);
    putshort(macfont->lastChar,resfile);
    putshort(macfont->widmax,resfile);
    putshort(macfont->kernMax,resfile);
    putshort(macfont->nDescent,resfile);
    putshort(macfont->fRectWidth,resfile);
    putshort(macfont->fRectHeight,resfile);
    putshort(macfont->owTLoc,resfile);
    putshort(macfont->ascent,resfile);
    putshort(macfont->descent,resfile);
    putshort(macfont->leading,resfile);
    putshort(macfont->rowWords,resfile);
    for ( i=0; i<macfont->fRectHeight; ++i ) {
	for ( j=0; j<macfont->rowWords; ++j )
	    putshort( macfont->rows[i][j],resfile );
    }
    for ( i=0; i<258; ++i )
	putshort(macfont->locs[i],resfile);
    for ( i=0; i<258; ++i )
	putshort(macfont->widths[i],resfile);

    if ( size!=ftell(resfile)-here-4 )
	printf( "IE: expected %d found %d\n", size, ftell(resfile)-here-4 );
    size = ftell(resfile)-here-4;
    fseek(resfile,here,SEEK_SET);
    putlong(size,resfile);
    fseek(resfile,0,SEEK_END);
return( here );
}
