updateAlbum(FXint & result,const GMTrack & track,FXint artist){
  result=-1;
  try {
    query_album.setParameter(0,track.album);
    query_album.setParameter(1,artist);
    query_album.execute();
    query_album.getResult(0,result);
    query_album.reset();

    if (result==-1) {
      insert_album.setParameter(0,track.album);
      insert_album.setParameter(1,artist);
      insert_album.setParameter(2,track.year);
      insert_album.setParameter(3,track.album_gain);
      insert_album.setParameter(4,track.album_peak);
      insert_album.execute();
      result = db.lastInsertRow();
      insert_album.reset();
      }
    else {
      update_album.setParameter(0,track.year);
      update_album.setParameter(1,track.album_gain);
      update_album.setParameter(2,track.album_peak);
      update_album.setParameter(3,result);
      update_album.execute();
      update_album.reset();
      }
    }
  catch (FXExecuteException & e){
    fxmessage("Exception: %s\n",e.what());
    result=-1;
    return FALSE;
    }
  return true;
  }
