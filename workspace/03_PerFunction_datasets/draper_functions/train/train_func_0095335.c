_fillRect(UT_RGBColor& clr,
						   UT_sint32 xoff,
						   UT_sint32 yoff,
						   UT_uint32 iPos1,
						   UT_uint32 iLen,
						   UT_Rect &r,
						   GR_Graphics * )
{


	if (getGraphics()->queryProperties(GR_Graphics::DGP_SCREEN))
	{

		xxx_UT_DEBUGMSG(("Doing _fillRect red %d blue %d green %d\n",clr.m_red,clr.m_blu,clr.m_grn));
		_getPartRect(&r, xoff, yoff, iPos1, iLen);
		r.height = getLine()->getHeight();
		r.top = r.top + getAscent() - getLine()->getAscent();
		GR_Painter painter(getGraphics());
		painter.fillRect(clr, r.left, r.top, r.width, r.height);
	}
}
