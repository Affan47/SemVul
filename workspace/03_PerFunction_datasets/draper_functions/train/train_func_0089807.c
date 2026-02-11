_dxf_DRAW_ZOOMBOX (tdmInteractor I, void *udata,
			       float rot[4][4], int draw)
{

  DEFDATA(I, tdmZoomData) ;

  ENTRY(("_dxf_DRAW_ZOOMBOX (0x%x, 0x%x, 0x%x, %d)",
	 I, udata, rot, draw));

  if (draw) {

    if (_dxf_isFlagsSet(_dxf_SERVICES_FLAGS(), SF_INVALIDATE_BACKSTORE))
	_dxf_captureZoomBox(I, udata, rot);


    glColor3f (1.0, 1.0, 1.0) ;
    glLineWidth(1.0) ;
    glBegin(GL_LINE_STRIP) ;


    glVertex2f ((float)PDATA(x1)+0.5, (float)PDATA(y1)+0.5) ;
    glVertex2f ((float)PDATA(x2)+0.5, (float)PDATA(y1)+0.5) ;
    glVertex2f ((float)PDATA(x2)+0.5, (float)PDATA(y2)+0.5) ;
    glVertex2f ((float)PDATA(x1)+0.5, (float)PDATA(y2)+0.5) ;
    glVertex2f ((float)PDATA(x1)+0.5, (float)PDATA(y1)+0.5) ;

    glEnd() ;
    glFlush() ;
  }
  else
      _dxf_restoreZoomBox(I, udata, rot);

  EXIT((""));
}
