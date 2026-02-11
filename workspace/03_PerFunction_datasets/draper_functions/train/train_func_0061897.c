CreateDelete (tdmInteractor I, int x, int y, tdmInteractorReturn *R)
{


  DEFDATA(I,CursorData) ;
  DEFPORT(I_PORT_HANDLE) ;
  int id, new_box ;

  ENTRY(("CreateDelete(0x%x, %d, %d, 0x%x)", I, x, y, R));

  Config (I, tdmBothBufferDraw) ;
  y = YFLIP(y) ;

  if ((id = find_closest (I, x, y)) != -1)
    {

      if (PDATA(mode) != XmROAM_MODE)
	{
	  delete_cursor (I, id) ;
	  CallCursorCallbacks (I, tdmCURSOR_DELETE, id, 0, 0, 0, R) ;

	  draw_box(I) ;
	}

      RestoreConfig (I, tdmBothBufferDraw) ;
      EXIT((""));
      return ;
    }


  PDATA(Z) = line_of_sight (I, (double)(x), (double)(y), &new_box) ;

  if (PDATA(mode) == XmCURSOR_MODE)
    {

      PDATA(X) = x ;
      PDATA(Y) = y ;

      deselect_cursor(I) ;
      id = create_cursor(I) ;

      PDATA(xbuff)[id] = x ;
      PDATA(ybuff)[id] = y ;
      PDATA(zbuff)[id] = PDATA(Z) ;

      select_cursor (I, id) ;
      save_cursors_in_canonical_form (I, id) ;

      CallCursorCallbacks (I, tdmCURSOR_CREATE, id,
			   PDATA(X), PDATA(Y), PDATA(Z), R) ;
    }
  else if (PDATA(mode) == XmROAM_MODE)
    {

      _dxf_ERASE_CURSOR (I, PDATA(roam_xbuff), PDATA(roam_ybuff)) ;

      PDATA(X) = x ;
      PDATA(Y) = y ;

      PDATA(roam_xbuff) = x ;
      PDATA(roam_ybuff) = y ;
      PDATA(roam_zbuff) = PDATA(Z) ;

      select_cursor (I, 0) ;
      save_cursors_in_canonical_form (I, 0) ;

      CallCursorCallbacks (I, tdmCURSOR_MOVE, id,
			   PDATA(X), PDATA(Y), PDATA(Z), R);
    }


  PDATA(K) = 0 ;
  add2historybuffer (I, x, y) ;


  PDATA(pcx) = (int)PDATA(X) ;
  PDATA(pcy) = (int)PDATA(Y) ;

  if (new_box)
    {

      setup_bounding_box(I) ;
      restore_image(I) ;
      RestoreConfig (I, tdmBothBufferDraw) ;
      _dxfRedrawInteractorEchos(WINDOW(I)) ;


    }
  else
    {

      _dxf_ERASE_PREVIOUS_MARKS(I) ;
      draw_cursors(I);

      draw_box(I) ;
      RestoreConfig (I, tdmBothBufferDraw) ;
    }

  EXIT((""));
}
