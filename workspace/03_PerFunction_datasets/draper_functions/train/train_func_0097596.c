WriteChar(FILE *bdf,struct MacFontRec *font,int enc, int index,
	int size, FOND *mine, struct assoc *ass) {
    Rect rct;
    int width;
    short *widths = NULL;

    if ( mine!=NULL && ass!=NULL ) {
	int i;


	for ( i=0; i<mine->stylewidthcnt; ++i )
	    if ( mine->stylewidths[i].style == ass->style ) {
		widths = mine->stylewidths[i].widthtab;
	break;
	    }
    }

    if ( index==0 )
	fprintf(bdf,"STARTCHAR .notdef\n");
    else if ( index<256 && macnames[index]!=NULL )
	fprintf(bdf,"STARTCHAR %s\n", macnames[index]);
    else
	fprintf(bdf,"STARTCHAR char%04x\n", index );
    width = GetCharBBox(font,index,&rct);
    fprintf(bdf,"ENCODING %d\n", enc );
    fprintf(bdf,"SWIDTH %ld 0\n",
	    widths==NULL?width*1000L/size:((widths[index]*1000L+(1<<11))>>12) );
    fprintf(bdf,"DWIDTH %d 0\n", width );
    fprintf(bdf,"BBX %d %d %d %d\n", rct.width, rct.height, rct.left, rct.bottom );
    fprintf(bdf,"BITMAP\n" );
    WriteBitmap(bdf,font,index,&rct);
    fprintf(bdf,"ENDCHAR\n" );
}
