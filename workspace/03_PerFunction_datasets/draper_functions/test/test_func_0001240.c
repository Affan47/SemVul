on_wdrawareagrande_button_press_event  (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  int x,y;
  int piece;

  if (!selpossible || event->type!=GDK_BUTTON_PRESS)
    return TRUE;

  if (actiongrande != AN_none)
    tanreleaseifrot();

  x=event->x;
  y=event->y;

  if ( event->button!=3){
    if ( (piece=tanwichisselect(x,y))>=0 ){
      taninitselect(piece, FALSE);
      selectedgrande=TRUE;
      actiongrande=AN_move;
      xold=x;
      yold=y;
      tandrawselect(0,0,0);
    }
    else{
      if (selectedgrande){
	actiongrande=AN_rot;
	xact=(gint16)(ARON+figgrande.piecepos[PIECENBR-1].posx*
		      widgetgrande->allocation.width*figgrande.zoom);
	yact=(gint16)(ARON+figgrande.piecepos[PIECENBR-1].posy*
		      widgetgrande->allocation.width*figgrande.zoom);
	xoth=xold=x;
	yoth=yold=y;
	rotact=tanangle((double)(xact-x),(double)(y-yact));
	rotold=0;

	invx2=x;
	invy2=y;
	gdk_draw_line (widgetgrande->window,
		       invertgc,
		       xact,yact,invx2,invy2);

      }
    }
  }

  if (event->button==3 && selectedgrande==TRUE){
    if (figgrande.piecepos[PIECENBR-1].type==3)
      figgrande.piecepos[PIECENBR-1].flipped^=1;
    else
      figgrande.piecepos[PIECENBR-1].rot=(figgrande.piecepos[PIECENBR-1].rot+TOUR/2)%TOUR;
    tandrawselect(0,0,0);
  }

  return TRUE;
}
