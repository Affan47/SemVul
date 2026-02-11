is_completed()
{
  gint j;
  gboolean done = TRUE;

  for(j=0; j<number_of_item_y; j++)
    {
      if(position[number_of_item_x+1][j]->color != position[number_of_item_x][j]->color)
	done = FALSE;
    }

  return done;
}
