midpoint_4(long pen, int x0, int y0, int x1, int y1)
{
    uint8_t * b=main_bitmap+y0+x0*bitmap_width;
    int dx=x1-x0;
    int dy=y1-y0;
    int d=2*dy-dx;
    int incrE=2*dy;
    int incrNE=2*(dy-dx);

    *b=pen;

    x1-=x0;

    while(x1) {
        x1--;

        if(d<=0) {
            d+=incrE;
            b-=bitmap_width;
        }
        else {
            d+=incrNE;
            b++;
            b-=bitmap_width;
        }
        *b=pen;
    }
}
