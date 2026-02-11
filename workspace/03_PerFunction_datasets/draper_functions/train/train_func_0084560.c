setStreamGenre(FXint id,const FXString & name){
  FXint genreid=-1;
  FXString query;
  try {


    query_genre.setParameter(0,name);
    query_genre.execute();
    query_genre.getResult(0,genreid);
    query_genre.reset();

    if (genreid==-1) {

      insert_genre.setParameter(0,name);
      insert_genre.execute();
      genreid = db.lastInsertRow();
      insert_genre.reset();
      }

    query.format("UPDATE streams SET genre = %d WHERE id==%d;",genreid,id);
    db.execute(query);
    }
  catch (FXExecuteException &){
    return false;
    }
  return true;
  }
