queryAlbum(FXint & album,FXint & year,FXint track){
  album=-1;
  year=0;
  try {
    query_album_with_track.setParameter(0,track);
    query_album_with_track.execute();
    query_album_with_track.getResult(0,album);
    query_album_with_track.getResult(1,year);
    query_album_with_track.reset();
    }
  catch (FXExecuteException &){
    album=-1;
    year=0;
    return false;
    }
  return true;
  }
