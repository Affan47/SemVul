drawcoloredtext(char *text) {
    char *buf = text, *ptr = buf, c = 1;
    unsigned long *col = dc.colors[0];
    int i, ox = dc.x;

    while( *ptr ) {
        for( i = 0; *ptr < 0 || *ptr > NUMCOLORS; i++, ptr++);
        if( !*ptr ) break;
        c=*ptr;
        *ptr=0;
        if( i ) {
            dc.w = selmon->ww - dc.x;
            drawtext(buf, col, False);
            dc.x += textnw(buf, i);
        }
        *ptr = c;
        col = dc.colors[ c-1 ];
        buf = ++ptr;
    }
    drawtext(buf, col, False);
    dc.x = ox;
}
