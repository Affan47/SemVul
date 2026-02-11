fload_map (Map *map, FILE *stream)
{
  gint ch;
  gint i, j;


  i = 0;
  j = 0;

  while ((ch = fgetc (stream)) != EOF)
  {

    switch (ch)
    {
    case SPACE:
    case WALL:
    case BADDIE:
    case PRIZE:
    case FOOD:
      map->_map[j][i] = ch;
      break;

    case '\n':

      break;

    default:

      map->_map[j][i] = SPACE;
      break;
    }


    if (ch == '\n')
    {

      while (i < map->size.num_cols)
      {
        map->_map[j][i++] = WALL;
      }
    }


    if (++i >= map->size.num_cols)
    {

      ++j;
      i = 0;


      while (ch != '\n')
      {
        ch = fgetc (stream);
      }
    }

    if (j >= map->size.num_rows)
    {

      return;
    }
  }


  if (i > 0)
  {
    ++j;
  }

  for (i = 0; i < map->size.num_cols; i++)
  {
    map->_map[j][i] = WALL;
  }
}
