PSDrawDoPoly(GPSWindow ps, GPoint *pt, int cnt, char *command) {
    int i;

    if ( pt[cnt-1].x==pt[0].x && pt[cnt-1].y==pt[0].y )
	--cnt;
    _GPSDraw_FlushPath(ps);
    if ( cnt==4 ) {
	fprintf( ps->output_file, "  %g %g  %g %g  %g %g  %g %g g_quad ",
		_GSPDraw_XPos(ps,pt[3].x), _GSPDraw_YPos(ps,pt[3].y),
		_GSPDraw_XPos(ps,pt[2].x), _GSPDraw_YPos(ps,pt[2].y),
		_GSPDraw_XPos(ps,pt[1].x), _GSPDraw_YPos(ps,pt[1].y),
		_GSPDraw_XPos(ps,pt[0].x), _GSPDraw_YPos(ps,pt[0].y));
    } else {
	PSMoveTo(ps,pt[0].x,pt[0].y);
	for ( i=1; i<cnt; ++i )
	    PSLineTo(ps,pt[i].x,pt[i].y);
    }
    fprintf( ps->output_file, "closepath %s %%Polygon\n", command );
    ps->pnt_cnt = 0;
    ps->cur_x = ps->cur_y = -1;
}
