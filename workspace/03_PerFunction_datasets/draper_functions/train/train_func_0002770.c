draw(GR_Graphics *gc, UT_Rect &rect, UT_sint32 iColumns, bool bLineBetween, double maxHeightPercent, double SpacePercent)
{
	GR_Painter painter(gc);

	UT_sint32 iHalfColumnGap = gc->tlu (rect.width / gc->tlu(20));

	UT_sint32 y_start = rect.top + iHalfColumnGap;
	UT_sint32 y_end = rect.top + rect.height - iHalfColumnGap;

	UT_sint32 y_step = gc->tlu(4);
	maxHeightPercent /= 100.0;
	SpacePercent /= 100.0;
	if(maxHeightPercent < 0.01)
		maxHeightPercent = 1.1;

	gc->setLineWidth(gc->tlu(1));
	UT_RGBColor Line_color(0, 0, 0);
	gc->setColor(Line_color);

	rect.left += iHalfColumnGap;
	rect.width -= 2 * iHalfColumnGap;
	double d_ysize = (double) (y_end - y_start);
	UT_sint32 iSpace = static_cast<UT_sint32>(SpacePercent* d_ysize);
	if(iSpace < y_step)
	  iSpace = y_step;
	UT_sint32 maxHeight = static_cast<UT_sint32>(maxHeightPercent * d_ysize);
	for (UT_sint32 i = 1; i <= iColumns; i++)
	{
		UT_sint32 curskip = 0;
		for(UT_sint32 y = y_start; y < y_end; y += y_step)
		{
			UT_sint32 xLeft, xRight;


			xLeft = rect.left + iHalfColumnGap + ((i-1) * rect.width/iColumns);
			xRight = rect.left - iHalfColumnGap + (i * rect.width / iColumns);
			curskip += y_step;
			if(curskip >= maxHeight )
			{
					curskip = 0;
					y += iSpace;
			}
			painter.drawLine(xLeft, y, xRight, y);
		}
	}

	if(bLineBetween)
	{

		for (UT_sint32 j = 2; j <= iColumns; j++)
		{
			UT_sint32 x = rect.left + (j-1) * rect.width / iColumns;
			painter.drawLine(x, y_start, x, y_end);
		}
	}
}
