draw_BWLine(void)
{
    int truex1 = mainViewer->xOnWindow(x1_);
    int truex2 = mainViewer->xOnWindow(x2_);
    int truey1 = mainViewer->yOnWindow(y1_);
    int truey2 = mainViewer->yOnWindow(y2_);


    if (selected())
	fl_color(FL_RED);
    else
	fl_color(FL_BLACK);
    fl_line(truex1+1, truey1+1, truex2+1, truey2+1);
    fl_line(truex1-1, truey1, truex2-1, truey2);


    if (selected())
	fl_color(FL_GREEN);
    else
	fl_color(FL_WHITE);
    fl_line(truex1, truey1, truex2, truey2);

}
