insertTrackInPlaylist(FXint playlist,FXIntList & tracks) {
  FXint queue=0;
  try {
    query_playlist_queue.setParameter(0,playlist);
    query_playlist_queue.execute();
    query_playlist_queue.getResult(0,queue);
    query_playlist_queue.reset();


    queue++;

#ifdef DEBUG
    FXlong start = fxgetticks();
#endif

    db.begin();
    for (int i=0;i<tracks.no();i++){
      insert_track_playlist.setParameter(0,playlist);
      insert_track_playlist.setParameter(1,tracks[i]);
      insert_track_playlist.setParameter(2,queue++);
      insert_track_playlist.execute();
      insert_track_playlist.reset();
      }
    db.commit();

#ifdef DEBUG
    FXlong end = fxgetticks();
    fxmessage("insertTrackInPlaylist %ld\n",end-start);
#endif
    }
  catch (FXCompileException & e){
    fxmessage("Compile Exception: %s\n",e.what());
    return false;
    }
  catch (FXExecuteException & e){
    fxmessage("Execute Exception: %s\n",e.what());
    return false;
    }
  return true;
  }
