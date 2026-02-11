ViewRoll (tdmInteractor I, int x, int y, int flag, int s)
{
  float rot[4][4], from[3], zaxis[3], Near, Far ;
  DEFDATA(I,tdmRotateData) ;
  DEFPORT(I_PORT_HANDLE) ;

  ENTRY(("ViewRoll(0x%x, %d, %d)", I, x, y));


  if (!PlaneRoll (I, x, y, rot))
    {
      EXIT(("PlaneRoll returns 0"));
      return ;
    }

  if (CDATA(view_coords_set))

      orbitFrom(rot, PDATA(strXfm), CDATA(to), CDATA(vdist)) ;


  MULTMATRIX (CDATA(viewXfm), PDATA(strXfm), rot) ;


  GET_VC_ORIGIN(CDATA(viewXfm), from) ;
  GET_VIEW_DIRECTION(CDATA(viewXfm), zaxis) ;
  _dxfGetNearFar(CDATA(projection), CDATA(w),
		CDATA(projection)? CDATA(fov): CDATA(width),
		from, zaxis, CDATA(box), &Near, &Far);


  if (CDATA(projection))
    {
      _dxfSetProjectionInfo(CDATA(stack), 1, CDATA(fov), CDATA(aspect),
			   Near, Far);
      _dxf_SET_PERSPECTIVE_PROJECTION(PORT_CTX, CDATA(fov), CDATA(aspect),
				     Near, Far);
    }
  else
    {
      _dxfSetProjectionInfo(CDATA(stack), 0, CDATA(width), CDATA(aspect),
			   Near, Far);
      _dxf_SET_ORTHO_PROJECTION(PORT_CTX, CDATA(width), CDATA(aspect),
			       Near, Far);
    }


  _dxf_LOAD_MATRIX (PORT_CTX, CDATA(viewXfm)) ;
  _dxfLoadViewMatrix (CDATA(stack), CDATA(viewXfm)) ;
  CDATA(view_state)++ ;


  CALLFUNC(I,EchoFunc) (I, UDATA(I), CDATA(viewXfm), 0) ;
  CALLFUNC(I,EchoFunc) (I, UDATA(I), CDATA(viewXfm), 1) ;

  PDATA(rotation_update) = 1 ;

  EXIT((""));
}
