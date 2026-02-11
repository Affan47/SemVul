insertTrackInPlaylist(FXint playlist,FXint & track) {
  FXint queue=0;
  try {
    GMQuery queu_query(&db,"SELECT MAX(queue) FROM playlist_tracks WHERE playlist == ?;");
    queu_query.setParameter(0,playlist);
    queu_query.execute();
    queu_query.getResult(0,queue);
    queu_query.reset();


    queue++;

    GMQuery insert_query(&db,"INSERT INTO playlist_tracks VALUES ( ? , ? , ?);");
    insert_query.setParameter(0,playlist);
    insert_query.setParameter(1,track);
    insert_query.setParameter(2,queue);
    insert_query.execute();

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
