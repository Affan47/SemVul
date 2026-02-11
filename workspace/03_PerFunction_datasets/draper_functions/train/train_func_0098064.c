removeTracksFromPlaylist(const FXIntList & queue,FXint playlist){
  FXString query;

  db.begin();

  if (queue.no()==1) {

    query.format("DELETE FROM playlist_tracks WHERE playlist == %d AND queue == %d;",playlist,queue[0]);
    if (!db.execute(query))
      goto error;


    query.format("UPDATE playlist_tracks SET queue = queue - 1 WHERE playlist == %d AND queue > %d;",playlist,queue[0]);
    if (!db.execute(query))
      goto error;
    }
  else {
    query.format("DELETE FROM playlist_tracks WHERE playlist == %d AND queue IN ( %d",playlist,queue[0]);
    for (FXint i=1;i<queue.no();i++){
      query+=",";
      query+=GMStringVal(queue[i]);
      }
    query+=");";

    if (!db.execute(query))
      goto error;

    if (!reorderPlaylists())
      goto error;
    }
  db.commit();
  return true;
error:
  db.rollback();
  return false;
  }
