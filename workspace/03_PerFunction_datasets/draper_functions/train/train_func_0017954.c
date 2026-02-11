find_visible_part(w,x,y,width,height)
Widget    w;
Position  *x;
Position  *y;
Dimension *width;
Dimension *height;
{
    Position root_x,root_y;
    Widget   p = w;

    *width  = w->core.width;
    *height = w->core.height;
    XtTranslateCoords(w,0,0,&root_x,&root_y);

    *x = 0;
    *y = 0;

    while(p = XtParent(p))
    {
        Position  rx,ry;
        Dimension w,h;


        XtTranslateCoords(p,0,0,&rx,&ry);

        w = p->core.width;
        h = p->core.height;


        if(w < *width)  *width  = w;
        if(h < *height) *height = h;

        if(rx>root_x) root_x = rx;
        if(ry>root_y) root_y = ry;


        if(XtIsShell(p)) break;
    }


    XtTranslateCoords(w,0,0,x,y);
    *x = root_x - *x;
    *y = root_y - *y;


}
