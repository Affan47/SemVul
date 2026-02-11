AddNode( const Unit *u, const PathNode &from,
                                 PathNode &to ) const {
  bool rc = false;

  if ( NextTo( u->Position(), to.pos ) &&
     (u->Terrain() & map->TerrainTypes(to.pos)) ) {
    Unit *m = map->GetUnit( to.pos );

    if ( m && m->IsMine() ) {
      bool enemy = false;

      if ( m->Owner() != u->Owner() ) {
        Point adj[6];
        map->GetNeighbors( to.pos, adj );
        for ( int i = NORTH; (i <= NORTHWEST) && !enemy; ++i ) {
          if ( adj[i].x != -1 ) {
            Unit *e = map->GetUnit( adj[i] );
            if ( e && (e->Owner() == m->Owner()) && !e->IsMine() ) enemy = true;
          }
        }
      }

      if ( !enemy ) {
        to.cost = 0;
        to.eta = ETA( to.pos );
        rc = true;
      }
    }
  }
  return rc;
}
