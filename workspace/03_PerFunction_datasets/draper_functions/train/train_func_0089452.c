calculate_position (GtkWidget *ardesia_bar_window,
                    gint       d_width,
                    gint       d_height,
                    gint      *x,
                    gint      *y,
                    gint       w_width,
                    gint       w_height,
                    gint       position)
{
  *y = ((d_height - w_height - SPACE_FROM_BORDER)/2);

  if (position==WEST)
    {
      *x = 0;
    }
  else if (position==EAST)
    {
      *x = d_width - w_width;
    }
  else
    {

      *x = (d_width - w_width)/2;
      if (position==NORTH)
        {
          *y = SPACE_FROM_BORDER;
        }
      else if (position==SOUTH)
        {

          *y = d_height - SPACE_FROM_BORDER - w_height;
        }
      else
        {

          perror ("Valid positions are NORTH, SOUTH, WEST or EAST\n");
          exit (EXIT_FAILURE);
        }
    }
}
