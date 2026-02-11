AM_drawMarks(void)
{
    int i, fx, fy, w, h;

    for (i=0;i<AM_NUMMARKPOINTS;i++)
    {
	if (markpoints[i].x != -1)
	{


	    w = 5;
	    h = 6;
	    fx = CXMTOF(markpoints[i].x);
	    fy = CYMTOF(markpoints[i].y);
	    if (fx >= f_x && fx <= f_w - w && fy >= f_y && fy <= f_h - h)
		V_DrawPatch(fx, fy, marknums[i]);
	}
    }

}
