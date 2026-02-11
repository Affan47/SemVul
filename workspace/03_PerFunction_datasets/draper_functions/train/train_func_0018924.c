DrawRoundTab(GWindow gw, GRect *pos,int inset,int radius,
	Color col1, Color col2, Color col3, Color col4) {
    int off;
    if ( inset<radius ) {
	off = radius;
	DrawULArc(gw,pos,inset,radius,col1);
	DrawURArc(gw,pos,inset,radius,col3);
    } else
	off = inset;
    GDrawDrawLine(gw,pos->x+inset,pos->y+off,pos->x+inset,pos->y+pos->height-1,col1);
    GDrawDrawLine(gw,pos->x+off,pos->y+inset,pos->x+pos->width-1-off,pos->y+inset,col2);
    GDrawDrawLine(gw,pos->x+pos->width-1-inset,pos->y+off,pos->x+pos->width-1-inset,pos->y+pos->height-1,col3);
}
