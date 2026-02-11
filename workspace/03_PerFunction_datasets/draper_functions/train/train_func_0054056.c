con_room_history_clear(cnr room)
{
  int h;

  if(room->master->history > 0)
  {

    h = room->hlast;

    while(1)
    {
      h++;

      if(h == room->master->history)
        h = 0;

      if (room->history[h] != NULL)
      {
        log_debug(NAME, "[%s] Clearing history entry %d", FZONE, h);
        xmlnode_free(room->history[h]->x);
        pool_free(room->history[h]->p);
      }
      else
      {
        log_debug(NAME, "[%s] skipping history entry %d", FZONE, h);
      }

      if(h == room->hlast)
        break;
    }
  }

}
