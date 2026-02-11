listGenres(FXComboBox * list,FXbool insert_default){
  register int i=0;
  FXDict genres;
  FXString name;
  FXint id;
  try {
    if (insert_default) {
      for (i=0;!TagLib::ID3v1::genre(i).isNull();i++) {
        genres.insert(TagLib::ID3v1::genre(i).toCString(true),(void*)(FXival)1);
        list->appendItem(TagLib::ID3v1::genre(i).toCString(true));
        }
      while(list_genres.execute()) {
        list_genres.getResult(0,id);
        list_genres.getResult(1,name);
        if (!genres.find(name.text()))
          list->appendItem(name);
        }
      }
    else {
      while(list_genres.execute()) {
        list_genres.getResult(0,id);
        list_genres.getResult(1,name);
        list->appendItem(name);
        }
      }
    list_genres.reset();
    list->sortItems();
    }
  catch(FXExecuteException &){
    list->clearItems();
    return FALSE;
    }
  return true;
  }
