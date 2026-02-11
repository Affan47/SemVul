client_process_msg_s_state (struct state *st, struct msg_s_data *msg) {

  if (ntohl( msg->time ) <= st->time) return -1;

  int p, i, j;
  for (p=0; p<MAX_PLAYER; ++p) {
    st->country[p].gold = ntohl( msg->gold[p] );

    st->fg[p].width = msg->width;
    st->fg[p].height = msg->height;
  }

  st->time = ntohl( msg->time );

  st->controlled = msg->control;

  st->grid.width = msg->width;
  st->grid.height = msg->height;

  for (i=0; i<MAX_WIDTH; ++i) {
    for (j=0; j<MAX_HEIGHT; ++j) {
      st->grid.tiles[i][j].cl = msg->tile[i][j];

      for (p=0; p<MAX_PLAYER; ++p)
        st->grid.tiles[i][j].units[p][citizen] = 0;

      st->grid.tiles[i][j].pl = msg->owner[i][j];
      st->grid.tiles[i][j].units[msg->owner[i][j]][citizen] = ntohs( msg->pop[i][j] );

      for (p=0; p<MAX_PLAYER; ++p){
        st->fg[p].call[i][j] = 0;
        if ( (msg->flag[i][j] & (1<<p)) == 0)
          st->fg[p].flag[i][j] = 0;
        else
          st->fg[p].flag[i][j] = 1;
      }
    }
  }
  return 0;
}
