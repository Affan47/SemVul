GetVector ( BasePoint *top,BasePoint *bottom,int orth ) {
    real catx, caty, hyp, temp;
    BasePoint ret;

    catx = top->x - bottom->x; caty = top->y - bottom->y;
    hyp = sqrt(( catx*catx ) + ( caty*caty ));
    ret.y = caty/hyp; ret.x = catx/hyp;

    if( orth ) {
        temp = ret.x; ret.x = -ret.y; ret.y = temp;
    }
return( ret );
}
