Hit( unsigned short damage ) {
  if ( IsAlive() ) {

    if ( u_group <= damage ) {
      u_group = 0;
      SetFlags( U_DESTROYED );
      u_pos.x = u_pos.y = -1;

      if ( !IsDummy() ) u_player->Units( -1 );
      return true;
    }

    u_group -= damage;
  }
  return false;
}
