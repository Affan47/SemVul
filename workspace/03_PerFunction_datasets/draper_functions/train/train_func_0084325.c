RestoreConfig (tdmInteractor I, tdmInteractorRedrawMode redrawMode)
{
  float M[4][4] ;
  int left, right, bottom, top ;
  DEFDATA(I,CursorData) ;
  DEFPORT(I_PORT_HANDLE) ;

  ENTRY(("RestoreConfig(0x%x, %d)", I, redrawMode));


  _dxfPopViewport (CDATA(stack)) ;
  _dxfGetViewport (CDATA(stack), &left, &right, &bottom, &top) ;
  _dxf_SET_VIEWPORT (PORT_CTX, left, right, bottom, top) ;


  if (CDATA(projection))
      _dxf_SET_PERSPECTIVE_PROJECTION (PORT_CTX, CDATA(fov), CDATA(aspect),
				      CDATA(Near), CDATA(Far)) ;
  else
      _dxf_SET_ORTHO_PROJECTION (PORT_CTX, CDATA(width), CDATA(aspect),
				CDATA(Near), CDATA(Far)) ;


  _dxfPopViewMatrix(CDATA(stack)) ;
  _dxfGetViewMatrix (CDATA(stack), M) ;
  _dxf_LOAD_MATRIX (PORT_CTX, M) ;


  if (CDATA(zbuffer))
      _dxf_SET_ZBUFFER_STATUS (PORT_CTX, 1) ;


  _dxf_BUFFER_RESTORE_CONFIG
      (PORT_CTX, PDATA(displaymode), PDATA(buffermode), redrawMode) ;

  EXIT((""));
}
