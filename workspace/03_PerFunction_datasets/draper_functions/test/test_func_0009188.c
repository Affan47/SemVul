FreePix ()

{
  GdkRectangle update_rect;
  int i;

  gdk_draw_rectangle (picture,
		      background_gc,
		      TRUE, 0, 0,
		      (gint)drawing_area->allocation.width,
		      (gint)drawing_area->allocation.height);
  if (gridtype==1) {
  	for (i=0+gridx;i<=(int)drawing_area->allocation.width;i=i+50)
  	    gdk_draw_line (picture, drawing_area->style->bg_gc[GTK_STATE_INSENSITIVE],
		   (gint) (i * size_factor), (gint) (0),
		   (gint) (i * size_factor), (gint) (drawing_area->allocation.height));
	for (i=0+gridy;i<=(int)drawing_area->allocation.height;i=i+50)
	    gdk_draw_line (picture, drawing_area->style->bg_gc[GTK_STATE_INSENSITIVE],
		   (gint) (0), (gint) (i*size_factor),
		   (gint) (drawing_area->allocation.width), (gint) (i * size_factor));
		}
   if (gridtype==2){

	for (i=-2560+gridx;i<=5280;i=i+64){
	    gdk_draw_line (picture, drawing_area->style->bg_gc[GTK_STATE_INSENSITIVE],
		   (gint) (0+gridx), (gint) ((gridy+i)*size_factor),
		   (gint) (5500+gridx)*size_factor,
		   (gint) (3200+gridy+i) * size_factor);
	    gdk_draw_line (picture, drawing_area->style->bg_gc[GTK_STATE_INSENSITIVE],
		   (gint) (0+gridx), (gint) ((i+gridy)*size_factor),
		   (gint) (5500+gridx)*size_factor,
		   (gint) (-3200+gridy+i) * size_factor);
			}
		}

  update_rect.x = 0;
  update_rect.y = 0;
  update_rect.width = drawing_area->allocation.width;
  update_rect.height = drawing_area->allocation.height;
  gtk_widget_draw ((GtkWidget *) drawing_area, &update_rect);

}
