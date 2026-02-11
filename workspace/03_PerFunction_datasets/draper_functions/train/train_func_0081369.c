ProcessObjective( AIObj &obj ) {

  for ( AIObj::AIAllocNode *n = static_cast<AIObj::AIAllocNode *>( obj.alloc_units.Head() );
        n; n = static_cast<AIObj::AIAllocNode *>(n->Next()) ) {
    Unit *u = n->unit;

    if ( u->IsReady() ) {
      Gam->SelectUnit( u );
      CommandUnit( u, obj );
    }
  }
}
