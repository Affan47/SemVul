GXDrawPathFill(GWindow w,Color col) {
    if ( !((GXWindow) w)->usecairo )
return;
    _GXCDraw_PathFill(w,col);
}
