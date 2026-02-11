gtk_plot_text_get_area(const gchar *text, gint angle, GtkJustification just,
                       const gchar *font, gint font_height,
                       gint *x, gint *y,
                       gint *width, gint *height)
{
  gint ascent, descent;

  if(text == NULL) return;

  gtk_plot_text_get_size(text, angle, font,
                         font_height,
                         width, height, &ascent, &descent);

  *x = 0;
  *y = 0;

  switch(just){
    case GTK_JUSTIFY_LEFT:
      switch(angle){
        case 0:
            *y -= ascent;
            break;
        case 90:
            *y -= *height;
            *x -= ascent;
            break;
        case 180:
            *x -= *width;
            *y -= descent;
            break;
        case 270:
            *x -= descent;
            break;
      }
      break;
    case GTK_JUSTIFY_RIGHT:
      switch(angle){
        case 0:
            *x -= *width;
            *y -= ascent;
            break;
        case 90:
            *x -= ascent;
            break;
        case 180:
            *y -= descent;
            break;
        case 270:
            *y -= *height;
            *x -= descent;
            break;
      }
      break;
    case GTK_JUSTIFY_CENTER:
    default:
      switch(angle){
        case 0:
            *x -= *width / 2.;
            *y -= ascent;
	    break;
        case 90:
            *x -= ascent;
            *y -= *height / 2.;
	    break;
        case 180:
            *x -= *width / 2.;
            *y -= descent;
            break;
        case 270:
            *x -= descent;
            *y -= *height / 2.;
            break;
      }
  }

}
